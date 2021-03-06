#ifndef SHARDDATABASEMANAGER_H
#define SHARDDATABASEMANAGER_H

#include "System/Containers/HashMap.h"
#include "System/Containers/InSortedList.h"
#include "System/Containers/InTreeMap.h"
#include "Framework/Storage/StorageEnvironment.h"
#include "Framework/Storage/StorageShardProxy.h"
#include "Framework/Storage/StorageAsyncGet.h"
#include "Framework/Storage/StorageAsyncList.h"
#include "Application/ConfigState/ConfigState.h"
#include "Application/Common/ClientRequest.h"
#include "ShardMessage.h"

class ShardServer;              // forward
class ShardDatabaseManager;     // forward


/*
===============================================================================================

 ShardDatabaseSequenceKey

===============================================================================================
*/

class ShardDatabaseSequence
{
    typedef InTreeNode<ShardDatabaseSequence> TreeNode;

public:
    ShardDatabaseSequence();

    uint64_t    tableID;
    Buffer      key;
    uint64_t    nextValue;
    uint64_t    remaining;

    TreeNode    treeNode;
};


/*
===============================================================================================
 
 ShardDatabaseAsyncGet -- helper class for async GET operation
 
===============================================================================================
*/

class ShardDatabaseAsyncGet : public StorageAsyncGet
{
public:
    ClientRequest*          request;
    ShardDatabaseManager*   manager;
    bool                    active;
    bool                    async;
    
    void                    OnRequestComplete();
};

/*
===============================================================================================
 
 ShardDatabaseAsyncList -- helper class for async LIST operation
 
===============================================================================================
*/

class ShardDatabaseAsyncList : public StorageAsyncList
{
public:
    ShardDatabaseAsyncList* next;
    ShardDatabaseAsyncList* prev;
    
    ShardDatabaseAsyncList(ShardDatabaseManager* manager);

    void                    SetRequest(ClientRequest* request);
    void                    SetTotal(uint64_t total);

    void                    OnShardComplete();
    void                    OnRequestComplete();
    void                    TryNextShard();
    bool                    IsActive();

private:
    ShardDatabaseManager*   manager;
    ClientRequest*          request;
    uint64_t                total;
};

/*
===============================================================================================

 ShardDatabaseManager

===============================================================================================
*/

class ShardDatabaseManager
{
    typedef HashMap<uint64_t, StorageShardProxy*>   ShardMap;
    typedef InList<ClientRequest>                   ClientRequestList;
    typedef InTreeMap<ShardDatabaseSequence>        Sequences;
    typedef InList<ShardDatabaseAsyncList>          ShardDatabaseAsyncListList;

    friend class ShardDatabaseAsyncGet;
    friend class ShardDatabaseAsyncList;

public:
    ShardDatabaseManager();

    void                        Init(ShardServer* shardServer);
    void                        Shutdown();
    
    StorageEnvironment*         GetEnvironment();
    StorageShardProxy*          GetQuorumPaxosShard(uint64_t quorumID);
    StorageShardProxy*          GetQuorumLogShard(uint64_t quorumID);
    ConfigState*                GetConfigState();
    
    void                        DeleteQuorum(uint64_t quorumID);

    void                        SetShards(SortedList<uint64_t>& shards);
    void                        SetQuorumShards(uint64_t quorumID);
    void                        RemoveDeletedDataShards(SortedList<uint64_t>& myShardIDs);
    
    void                        OnClientReadRequest(ClientRequest* request);
    void                        OnClientListRequest(ClientRequest* request);
    bool                        OnClientSequenceNext(ClientRequest* request);
    uint64_t                    ExecuteMessage(uint64_t quorumID, uint64_t paxosID, uint64_t commandID, ShardMessage& message);

    void                        OnLeaseTimeout();

    unsigned                    GetNumReadRequests();
    unsigned                    GetNumBlockingReadRequests();
    unsigned                    GetNumListRequests();
    unsigned                    GetNumInactiveListThreads();
    uint64_t                    GetNextListRequestID();
    uint64_t                    GetNumAbortedListRequests();
    uint64_t                    GetNextGetRequestID();
        
private:
    void                        DeleteQuorumPaxosShard(uint64_t quorumID);
    void                        DeleteQuorumLogShard(uint64_t quorumID);
    void                        DeleteDataShards(uint64_t quorumID);

    void                        OnExecuteReads();
    void                        OnExecuteLists();
    bool                        IsEmptyListRange(ClientRequest* request);

    ShardServer*                shardServer;
    StorageEnvironment          environment;
    StorageShardProxy           systemShard;
    ShardMap                    quorumPaxosShards;
    ShardMap                    quorumLogShards;
    ClientRequestList           readRequests;
    ClientRequestList           blockingReadRequests;
    ClientRequestList           listRequests;
    YieldTimer                  executeReads;
    ShardDatabaseAsyncGet       asyncGet;
    YieldTimer                  executeLists;
    unsigned                    numAsyncLists;
    ShardDatabaseAsyncList**    asyncLists;
    ShardDatabaseAsyncListList  inactiveAsyncLists;
    Sequences                   sequences;
    uint64_t                    nextListRequestID;
    uint64_t                    numAbortedListRequests;
    uint64_t                    nextGetRequestID;
};

#endif
