#ifndef SHARDDATABASEADAPTER_H
#define SHARDDATABASEADAPTER_H

#include "System/Containers/HashMap.h"
#include "Framework/Storage/StorageEnvironment.h"
#include "Framework/Storage/StorageShardProxy.h"
#include "Application/ConfigState/ConfigState.h"
#include "Application/Common/ClientRequest.h"
#include "ShardMessage.h"

class ShardServer; // forward

/*
===============================================================================================

 ShardDatabaseManager

===============================================================================================
*/

class ShardDatabaseManager
{
//    typedef HashMap<uint64_t, StorageDatabase*>     DatabaseMap;
//    typedef HashMap<uint64_t, StorageTable*>        TableMap;
    typedef HashMap<uint64_t, StorageShardProxy*>   ShardMap;

public:
    void                    Init(ShardServer* shardServer);
    void                    Shutdown();
    
    StorageEnvironment*     GetEnvironment();
//    StorageTable*           GetQuorumTable(uint64_t quorumID);
//    StorageTable*           GetTable(uint64_t tableID);
    StorageShardProxy*      GetQuorumShard(uint64_t quorumID);
    StorageShardProxy*      GetDataShard(uint64_t tableID);

    void                    SetShards(SortedList<uint64_t>& shards);
    void                    RemoveDeletedDatabases();
    void                    RemoveDeletedTables();
    
    void                    OnClientReadRequest(ClientRequest* request);
    void                    ExecuteMessage(uint64_t paxosID,
                             uint64_t commandID, ShardMessage& message, ClientRequest* request);
    
private:
    ShardServer*            shardServer;
    StorageEnvironment      environment;
//    StorageDatabase*        systemDatabase;
//    DatabaseMap             databases;
//    TableMap                tables;
    StorageShardProxy       systemShard;
    ShardMap                dataShards;
    ShardMap                quorumShards;
};

#endif
