#include "ConfigActivationManager.h"
#include "System/Events/EventLoop.h"
#include "Application/Common/DatabaseConsts.h"
#include "Application/Common/ContextTransport.h"
#include "ConfigServer.h"
#include "ConfigQuorumProcessor.h"

void ConfigActivationManager::Init(ConfigServer* configServer_)
{
    configServer = configServer_;
    
    activationTimeout.SetCallable(MFUNC(ConfigActivationManager, OnActivationTimeout));
}

void ConfigActivationManager::TryDeactivateShardServer(uint64_t nodeID)
{
    ConfigState*        configState;
    ConfigQuorum*       itQuorum;
    ConfigShardServer*  shardServer;

    configState = configServer->GetDatabaseManager()->GetConfigState();

    FOREACH(itQuorum, configState->quorums)
    {
        if (itQuorum->isActivatingNode && itQuorum->activatingNodeID == nodeID)
        {
            shardServer = configState->GetShardServer(itQuorum->activatingNodeID);
            assert(shardServer != NULL);

            itQuorum->ClearActivation();
            UpdateTimeout();

            Log_Message("Activation failed for shard server %U and quorum %U...",
             itQuorum->quorumID, itQuorum->activatingNodeID);
        }

        if (itQuorum->IsActiveMember(nodeID))
        {
            // if this node was part of an activation process, cancel it
            if (itQuorum->isActivatingNode)
            {
                shardServer = configState->GetShardServer(itQuorum->activatingNodeID);
                assert(shardServer != NULL);

                itQuorum->ClearActivation();
                UpdateTimeout();

                Log_Message("Activation failed for shard server %U and quorum %U...",
                 itQuorum->activatingNodeID, itQuorum->quorumID);
            }
            
            configServer->GetQuorumProcessor()->DeactivateNode(itQuorum->quorumID, nodeID);
        }
    }
}

void ConfigActivationManager::TryActivateShardServer(uint64_t nodeID, bool force)
{
    uint64_t            paxosID;
    ConfigState*        configState;
    ConfigQuorum*       itQuorum;
    ConfigShardServer*  shardServer;
    uint64_t            now;
    
    now = EventLoop::Now();
    
    Log_Trace();

    configState = configServer->GetDatabaseManager()->GetConfigState();
    shardServer = configState->GetShardServer(nodeID);

    FOREACH(itQuorum, configState->quorums)
    {
        Log_Trace("itQuorum->isActivatingNode: %b", itQuorum->isActivatingNode);
        if (itQuorum->isActivatingNode)
            continue;
            
        Log_Trace("itQuorum->hasPrimary: %b", itQuorum->hasPrimary);
        if (!itQuorum->hasPrimary)
            continue;

        if (itQuorum->IsInactiveMember(nodeID))
        {
            paxosID = QuorumInfo::GetQuorumInfo(shardServer->quorumInfos, itQuorum->quorumID)->paxosID;
            if (paxosID >= (itQuorum->paxosID - RLOG_REACTIVATION_DIFF) ||
             itQuorum->paxosID <= RLOG_REACTIVATION_DIFF)
            {
                if (!force && !shardServer->tryAutoActivation)
                    continue;

                // the shard server is "almost caught up", start the activation process
                itQuorum->OnActivationStart(nodeID, now + ACTIVATION_TIMEOUT);
                UpdateTimeout();
                
                shardServer->tryAutoActivation = false;

                Log_Message("Activation started for shard server %U and quorum %U...",
                 itQuorum->activatingNodeID, itQuorum->quorumID);
                configServer->OnConfigStateChanged();
            }
        }
    }    
}

void ConfigActivationManager::OnExtendLease(ConfigQuorum& quorum, ClusterMessage& message)
{
    ConfigState*        configState;
    ConfigShardServer*  shardServer;

    Log_Trace();

    if (!quorum.hasPrimary || message.nodeID != quorum.primaryID)
        return;

    configState = configServer->GetDatabaseManager()->GetConfigState();

    if (!quorum.isActivatingNode || quorum.isReplicatingActivation ||
     message.configID != quorum.configID)
    {
        Log_Trace("ExtendLease condition: %b %b %U %U", quorum.isActivatingNode,
        quorum.isReplicatingActivation,
        message.configID,
        quorum.configID);        
        return;
    }
        
    if (!quorum.isWatchingPaxosID)
    {
        Log_Message("Activating shard server %U in quorum %U: Starting to monitor the primary's paxosID",
         quorum.quorumID, quorum.activatingNodeID);
        
        quorum.OnActivationMonitoring(message.paxosID);
        configServer->OnConfigStateChanged();
    }
    else
    {
        Log_Trace();
        
        // if the primary was able to increase its paxosID, the new shardserver joined successfully
        if (message.paxosID > quorum.activationPaxosID)
        {
            Log_Message("Activating shard server %U in quorum %U: The primary was able to increase its paxosID!",
             quorum.quorumID, quorum.activatingNodeID);
            
            quorum.OnActivationReplication();
            configServer->OnConfigStateChanged();
            configServer->GetQuorumProcessor()->ActivateNode(quorum.quorumID, quorum.activatingNodeID);

            shardServer = configState->GetShardServer(quorum.activatingNodeID);
            shardServer->tryAutoActivation = true;
        }
        else
        {
            Log_Message("Activating shard server %U in quorum %U: The primary was not able to increase its paxosID so far...",
             quorum.quorumID, quorum.activatingNodeID);
        }
    }    
}

void ConfigActivationManager::OnActivationTimeout()
{
    uint64_t            now;
    ConfigState*        configState;
    ConfigQuorum*       itQuorum;
    ConfigShardServer*  shardServer;
    
    Log_Trace();
    
    now = EventLoop::Now();
    configState = configServer->GetDatabaseManager()->GetConfigState();
    
    FOREACH(itQuorum, configState->quorums)
    {
        if (itQuorum->activationExpireTime > 0 && itQuorum->activationExpireTime < now)
        {
            // stop activation
            
            assert(itQuorum->isActivatingNode == true);
            assert(itQuorum->isReplicatingActivation == false);

            shardServer = configState->GetShardServer(itQuorum->activatingNodeID);
            assert(shardServer != NULL);

            Log_Message("Activating shard server %U in quorum %U: Activation failed...",
             itQuorum->activatingNodeID, itQuorum->quorumID);

            itQuorum->ClearActivation();
             
            configServer->OnConfigStateChanged();
        }
    }
    
    UpdateTimeout();
}

void ConfigActivationManager::UpdateTimeout()
{
    ConfigQuorum*   it;
    uint64_t        activationExpireTime;
    
    Log_Trace();
    
    activationExpireTime = 0;
    FOREACH(it, configServer->GetDatabaseManager()->GetConfigState()->quorums)
    {
        if (it->isActivatingNode && !it->isReplicatingActivation)
        {
            if (activationExpireTime == 0 || it->activationExpireTime < activationExpireTime)
                activationExpireTime = it->activationExpireTime;
        }
    }
    
    if (activationExpireTime > 0)
    {
        activationTimeout.SetExpireTime(activationExpireTime);
        EventLoop::Reset(&activationTimeout);
    }
}
