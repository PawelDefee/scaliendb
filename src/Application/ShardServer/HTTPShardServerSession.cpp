#include "HTTPShardServerSession.h"
#include "ShardServer.h"
#include "Application/HTTP/UrlParam.h"
#include "Application/HTTP/HTTPConnection.h"
#include "Framework/Replication/ReplicationConfig.h"
#include "Version.h"

void HTTPShardServerSession::SetShardServer(ShardServer* shardServer_)
{
    shardServer = shardServer_;
}

void HTTPShardServerSession::SetConnection(HTTPConnection* conn_)
{
    session.SetConnection(conn_);
    conn_->SetOnClose(MFUNC(HTTPShardServerSession, OnConnectionClose));
}

bool HTTPShardServerSession::HandleRequest(HTTPRequest& request)
{
    ReadBuffer  cmd;
    UrlParam    params;
    
    session.ParseRequest(request, cmd, params);
    return ProcessCommand(cmd, params);
}

void HTTPShardServerSession::OnComplete(ClientRequest* request, bool last)
{
    Buffer          tmp;
    ReadBuffer      rb;
    ClientResponse* response;

    response = &request->response;
    switch (response->type)
    {
    case CLIENTRESPONSE_OK:
        session.PrintLine(ReadBuffer("OK"));
        break;
    case CLIENTRESPONSE_NUMBER:
        tmp.Writef("%U", response->number);
        rb.Wrap(tmp);
        session.PrintLine(rb);
        break;
    case CLIENTRESPONSE_VALUE:
        session.PrintLine(response->value);
        break;
    case CLIENTRESPONSE_NOSERVICE:
        session.PrintLine(ReadBuffer("NOSERVICE"));
        break;
    case CLIENTRESPONSE_FAILED:
        session.PrintLine(ReadBuffer("FAILED"));
        break;
    }
    
    if (last)
    {
        session.Flush();        
        delete request;
    }
}

bool HTTPShardServerSession::IsActive()
{
    return true;
}

void HTTPShardServerSession::PrintStatus()
{
    Buffer      buf;

    session.PrintPair("ScalienDB", "ShardServer");
    session.PrintPair("Version", VERSION_STRING);

    buf.Writef("%d", (int) REPLICATION_CONFIG->GetNodeID());
    buf.NullTerminate();
    session.PrintPair("NodeID", buf.GetBuffer());   

    // TODO: write quorums, shards, and leases
    
    session.Flush();
}

bool HTTPShardServerSession::ProcessCommand(ReadBuffer& cmd, UrlParam& params)
{
    ClientRequest*  request;
    
    if (HTTP_MATCH_COMMAND(cmd, ""))
    {
        PrintStatus();
        return true;
    }

    request = ProcessShardServerCommand(cmd, params);
    if (!request)
        return false;

    request->session = this;
    shardServer->OnClientRequest(request);
    
    return true;
}

ClientRequest* HTTPShardServerSession::ProcessShardServerCommand(ReadBuffer& cmd, UrlParam& params)
{
    if (HTTP_MATCH_COMMAND(cmd, "get"))
        return ProcessGet(params);
    if (HTTP_MATCH_COMMAND(cmd, "set"))
        return ProcessSet(params);
    if (HTTP_MATCH_COMMAND(cmd, "delete"))
        return ProcessDelete(params);
    
    return NULL;
}

ClientRequest* HTTPShardServerSession::ProcessGet(UrlParam& params)
{
    ClientRequest*  request;
    uint64_t        databaseID;
    uint64_t        tableID;
    ReadBuffer      key;
    ReadBuffer      value;
    
    HTTP_GET_U64_PARAM(params, "databaseID", databaseID);
    HTTP_GET_U64_PARAM(params, "tableID", tableID);
    HTTP_GET_PARAM(params, "key", key);

    request = new ClientRequest;
    request->Get(0, databaseID, tableID, key);

    return request;    
}

ClientRequest* HTTPShardServerSession::ProcessSet(UrlParam& params)
{
    ClientRequest*  request;
    uint64_t        databaseID;
    uint64_t        tableID;
    ReadBuffer      key;
    ReadBuffer      value;
    
    HTTP_GET_U64_PARAM(params, "databaseID", databaseID);
    HTTP_GET_U64_PARAM(params, "tableID", tableID);
    HTTP_GET_PARAM(params, "key", key);
    HTTP_GET_PARAM(params, "value", value);

    request = new ClientRequest;
    request->Set(0, databaseID, tableID, key, value);

    return request;    
}

ClientRequest* HTTPShardServerSession::ProcessDelete(UrlParam& params)
{
    ClientRequest*  request;
    uint64_t        databaseID;
    uint64_t        tableID;
    ReadBuffer      key;
    ReadBuffer      value;
    
    HTTP_GET_U64_PARAM(params, "databaseID", databaseID);
    HTTP_GET_U64_PARAM(params, "tableID", tableID);
    HTTP_GET_PARAM(params, "key", key);

    request = new ClientRequest;
    request->Delete(0, databaseID, tableID, key);

    return request;    
}

void HTTPShardServerSession::OnConnectionClose()
{
    shardServer->OnClientClose(this);
    session.SetConnection(NULL);
}
