#include "JSONConfigState.h"
#include "System/Macros.h"
#include "System/Config.h"
#include "Application/ConfigState/ConfigShardServer.h"
#include "ConfigServer.h"

#define JSON_STRING(obj, member) \
    json->PrintString(#member); \
    json->PrintColon(); \
    json->PrintString((obj)->member);

#define JSON_STRING_PRINTABLE(obj, member) \
    printable.Write((obj)->member); \
    { \
        bool isPrintable = true; \
        if (!printable.IsAsciiPrintable()) \
            isPrintable = false; \
        for (unsigned i = 0; i < printable.GetLength(); i++) \
            if (printable.GetCharAt(i) == '\\') \
                isPrintable = false; \
        if (!isPrintable) \
            printable.ToHexadecimal(); \
    } \
    json->PrintString(#member); \
    json->PrintColon(); \
    json->PrintString(printable);
    
#define JSON_NUMBER(obj, member) \
    json->PrintString(#member); \
    json->PrintColon(); \
    json->PrintNumber((obj)->member);

#define JSON_BOOL(obj, member) \
    json->PrintString(#member); \
    json->PrintColon(); \
    json->PrintBool((obj)->member);

#define JSON_IDLIST(obj, member) \
    json->PrintString(#member); \
    json->PrintColon(); \
    WriteIDList((obj)->member);


JSONConfigState::JSONConfigState()
{
    heartbeats = NULL;
    configState = NULL;
    json = NULL;
}

void JSONConfigState::SetHeartbeats(InSortedList<Heartbeat>* heartbeats_)
{
    heartbeats = heartbeats_;
}

void JSONConfigState::SetConfigState(ConfigState* configState_)
{
    configState = configState_;
}

void JSONConfigState::SetJSONBufferWriter(JSONBufferWriter* json_)
{
    json = json_;
}

void JSONConfigState::Write()
{
    JSON_NUMBER(configState, paxosID);
    json->PrintComma();

    WriteControllers();
    json->PrintComma();    
    WriteQuorums();
    json->PrintComma();
    WriteDatabases();
    json->PrintComma();
    WriteTables();
    json->PrintComma();
    WriteShards();
    json->PrintComma();
    WriteShardServers();
}

void JSONConfigState::WriteControllers()
{
    ConfigController*   controller;

    json->PrintString("master");
    json->PrintColon();
    if (configState->hasMaster)
        json->PrintNumber(configState->masterID);
    else
        json->PrintNumber(-1);
    json->PrintComma();
    
    json->PrintString("controllers");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH(controller, configState->controllers)
    {
        json->PrintObjectStart();

        json->PrintString("nodeID");
        json->PrintColon();
        json->PrintNumber(controller->nodeID);
        json->PrintComma();

        json->PrintString("endpoint");
        json->PrintColon();
        json->PrintString(controller->endpoint.ToString());
        json->PrintComma();

        json->PrintString("isConnected");
        json->PrintColon();
        json->PrintBool(controller->isConnected);

        json->PrintObjectEnd();
    }

    json->PrintArrayEnd();
}
    
void JSONConfigState::WriteQuorums()
{
    ConfigQuorum*   quorum;
    
    json->PrintString("quorums");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH (quorum, configState->quorums)
        WriteQuorum(quorum);

    json->PrintArrayEnd();
}

void JSONConfigState::WriteQuorum(ConfigQuorum* quorum)
{
    json->PrintObjectStart();
    
    JSON_NUMBER(quorum, quorumID);
    json->PrintComma();
    JSON_STRING(quorum, name);
    json->PrintComma();
    JSON_BOOL(quorum, hasPrimary);
    json->PrintComma();
    
    if (quorum->hasPrimary)
    {
        JSON_NUMBER(quorum, primaryID);
        json->PrintComma();
    }

    JSON_NUMBER(quorum, paxosID);
    json->PrintComma();

    json->PrintString("activeNodes");
    json->PrintColon();
    WriteIDList(quorum->activeNodes);
    json->PrintComma();

    json->PrintString("inactiveNodes");
    json->PrintColon();
    WriteIDList(quorum->inactiveNodes);
    json->PrintComma();

    json->PrintString("shards");
    json->PrintColon();
    WriteIDList(quorum->shards);

    json->PrintObjectEnd();
}

void JSONConfigState::WriteDatabases()
{
    ConfigDatabase*   database;
    
    json->PrintString("databases");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH (database, configState->databases)
        WriteDatabase(database);

    json->PrintArrayEnd();
}

void JSONConfigState::WriteDatabase(ConfigDatabase* database)
{
    json->PrintObjectStart();
    
    JSON_NUMBER(database, databaseID);
    json->PrintComma();
    JSON_STRING(database, name);
    json->PrintComma();
    JSON_IDLIST(database, tables);
    
    json->PrintObjectEnd();
}

void JSONConfigState::WriteTables()
{
    ConfigTable*   table;
    
    json->PrintString("tables");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH (table, configState->tables)
        WriteTable(table);

    json->PrintArrayEnd();
}

void JSONConfigState::WriteTable(ConfigTable* table)
{
    json->PrintObjectStart();
    
    JSON_NUMBER(table, tableID);
    json->PrintComma();
    JSON_NUMBER(table, databaseID);
    json->PrintComma();
    JSON_STRING(table, name);
    json->PrintComma();
    JSON_BOOL(table, isFrozen);
    json->PrintComma();
    JSON_IDLIST(table, shards);
    
    json->PrintObjectEnd();
}

void JSONConfigState::WriteShards()
{
    ConfigShard*   shard;
    
    json->PrintString("shards");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH (shard, configState->shards)
        WriteShard(shard);

    json->PrintArrayEnd();
}

void JSONConfigState::WriteShard(ConfigShard* shard)
{
    Buffer printable;
    
    json->PrintObjectStart();
    
    JSON_NUMBER(shard, shardID);
    json->PrintComma();
    JSON_NUMBER(shard, quorumID);
    json->PrintComma();
    JSON_NUMBER(shard, tableID);
    json->PrintComma();
    JSON_STRING_PRINTABLE(shard, firstKey);
    json->PrintComma();
    JSON_STRING_PRINTABLE(shard, lastKey);
    json->PrintComma();
    JSON_NUMBER(shard, shardSize);
    json->PrintComma();
    JSON_STRING_PRINTABLE(shard, splitKey);
    json->PrintComma();
    JSON_BOOL(shard, isSplitable);

    json->PrintObjectEnd();
}

void JSONConfigState::WriteShardServers()
{
    ConfigShardServer*   shardServer;
    
    json->PrintString("shardServers");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH (shardServer, configState->shardServers)
        WriteShardServer(shardServer);

    json->PrintArrayEnd();
}

void JSONConfigState::WriteShardServer(ConfigShardServer* server)
{
    QuorumInfo*         quorumInfo;
    QuorumShardInfo*    quorumShardInfo;
    QuorumPriority*     quorumPriority;
    
    json->PrintObjectStart();

    JSON_NUMBER(server, nodeID);
    json->PrintComma();

    json->PrintString("endpoint");
    json->PrintColon();
    json->PrintString(server->endpoint.ToReadBuffer());
    json->PrintComma();
    
    JSON_NUMBER(server, httpPort);
    json->PrintComma();
    JSON_NUMBER(server, sdbpPort);
    json->PrintComma();

    if (heartbeats)
    {
        json->PrintString("hasHeartbeat");
        json->PrintColon();
        json->PrintBool(HasHeartbeat(server->nodeID));
        json->PrintComma();
    }
    
    json->PrintString("quorumInfos");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH (quorumInfo, server->quorumInfos)
        WriteQuorumInfo(quorumInfo);

    json->PrintArrayEnd();

    json->PrintComma();
    
    json->PrintString("quorumShardInfos");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH (quorumShardInfo, server->quorumShardInfos)
        WriteQuorumShardInfo(quorumShardInfo);

    json->PrintArrayEnd();

    json->PrintComma();

    json->PrintString("quorumPriorities");
    json->PrintColon();
    json->PrintArrayStart();

    FOREACH (quorumPriority, server->quorumPriorities)
        WriteQuorumPriority(quorumPriority);

    json->PrintArrayEnd();

    json->PrintObjectEnd();
}

void JSONConfigState::WriteQuorumInfo(QuorumInfo* info)
{
    json->PrintObjectStart();

    JSON_NUMBER(info, quorumID);
    json->PrintComma();
    JSON_NUMBER(info, paxosID);
    json->PrintComma();
    JSON_BOOL(info, needCatchup);

    // for backward compatibility
    json->PrintComma();
    json->PrintString("isSendingCatchup");
    json->PrintColon();
    json->PrintBool(false);

    json->PrintObjectEnd();    
}

void JSONConfigState::WriteQuorumShardInfo(QuorumShardInfo* info)
{
    json->PrintObjectStart();

    JSON_NUMBER(info, shardID);
    json->PrintComma();
    JSON_BOOL(info, isSendingShard);
    
    if (info->isSendingShard)
    {
        json->PrintComma();
        JSON_NUMBER(info, migrationQuorumID);
        json->PrintComma();
        JSON_NUMBER(info, migrationNodeID);
        json->PrintComma();
        JSON_NUMBER(info, migrationBytesSent);
        json->PrintComma();
        JSON_NUMBER(info, migrationBytesTotal);
        json->PrintComma();
        JSON_NUMBER(info, migrationThroughput);
    }
    
    json->PrintObjectEnd();    
}

void JSONConfigState::WriteQuorumPriority(QuorumPriority* prio)
{
    json->PrintObjectStart();

    JSON_NUMBER(prio, quorumID);
    json->PrintComma();
    JSON_NUMBER(prio, priority);
    
    json->PrintObjectEnd();    
}

template<typename List>
void JSONConfigState::WriteIDList(List& list)
{
    uint64_t*   it;
    
    json->PrintArrayStart();
    FOREACH (it, list)
    {
        if (it != list.First())
            json->PrintComma();
        json->PrintNumber(*it);
    }
    json->PrintArrayEnd();
}

bool JSONConfigState::HasHeartbeat(uint64_t nodeID)
{
    Heartbeat* it;

    FOREACH (it, *heartbeats)
    {
        if (it->nodeID == nodeID)
            return true;
    }

    return false;
}
