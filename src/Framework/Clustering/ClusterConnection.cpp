#include "ClusterConnection.h"
#include "ClusterTransport.h"

void ClusterConnection::InitConnected(bool startRead)
{
    MessageConnection::InitConnected(startRead);
    
    Log_Trace();

    progress = INCOMING;
    nodeID = UNDEFINED_NODEID;
}

void ClusterConnection::SetTransport(ClusterTransport* transport_)
{
    Log_Trace();
    
    transport = transport_;
}

void ClusterConnection::SetNodeID(uint64_t nodeID_)
{
    nodeID = nodeID_;
}

void ClusterConnection::SetEndpoint(Endpoint& endpoint_)
{
    endpoint = endpoint_;
}

void ClusterConnection::SetProgress(Progress progress_)
{
    progress = progress_;
}

uint64_t ClusterConnection::GetNodeID()
{
    return nodeID;
}

Endpoint ClusterConnection::GetEndpoint()
{
    return endpoint;
}

ClusterConnection::Progress ClusterConnection::GetProgress()
{
    return progress;
}

void ClusterConnection::Close()
{
    if (state == CONNECTED && nodeID != UNDEFINED_NODEID)
        Log_Message("[%s] Cluster node %U closed", endpoint.ToString(), nodeID);

    MessageConnection::Close();
}

void ClusterConnection::Connect()
{
    progress = OUTGOING;
    MessageConnection::Connect(endpoint);
}

void ClusterConnection::OnConnect()
{
    Buffer      buffer;
    ReadBuffer  rb;

    MessageConnection::OnConnect();
    
    Log_Trace("endpoint = %s", endpoint.ToString());
    
    rb = transport->GetSelfEndpoint().ToReadBuffer();
    
    if (transport->IsAwaitingNodeID())
        buffer.Writef("*:%#R", &rb); // send *:endpoint
    else
    {
        buffer.Writef("%U:%U:%#R", 
         transport->GetClusterID(),
         transport->GetSelfNodeID(),
         &rb); // send my clusterID:nodeID:endpoint
    }
    Log_Trace("sending %B", &buffer);
    Write(buffer);
    
    Log_Trace("Conn READY to node %U at %s", nodeID, endpoint.ToString());

    if (nodeID != transport->GetSelfNodeID())
    {
        if (nodeID == UNDEFINED_NODEID)
            Log_Message("[%s] Cluster unknown node connected =>", endpoint.ToString());
        else
            Log_Message("[%s] Cluster node %U connected =>", endpoint.ToString(), nodeID);
    }
    else
        Log_Message("[%s] Cluster node connected to self", endpoint.ToString(), nodeID);

    progress = READY;
    OnWriteReadyness();
}

void ClusterConnection::OnClose()
{
    Log_Trace();
    
    if (connectTimeout.IsActive())
        return;
    
    MessageConnection::Close();
    if (nodeID != UNDEFINED_NODEID)
        Log_Message("[%s] Cluster node %U disconnected", endpoint.ToString(), nodeID);
    
    if (progress == INCOMING)
    {
        // we don't know the other side, delete conn
        transport->DeleteConnection(this);
    }
    else if (progress == READY)
    {
        // endpoint contains the other side, connect
        progress = OUTGOING;
        
        EventLoop::Reset(&connectTimeout);
    }
}

bool ClusterConnection::OnMessage(ReadBuffer& msg)
{
    uint64_t            nodeID_;
    uint64_t            clusterID_;
    ReadBuffer          buffer;
    ClusterConnection*  dup;
    Endpoint            remoteEndpoint;

    if (progress == ClusterConnection::INCOMING)
    {
        // we have no incoming connections if we don't have a nodeID
        assert(transport->IsAwaitingNodeID() == false);

        // the node at the other end is awaiting its nodeID
        if (msg.GetCharAt(0) == '*')
        {
            msg.Readf("*:%#R", &buffer);
            endpoint.Set(buffer);
            progress = ClusterConnection::AWAITING_NODEID;
            Log_Trace("Conn is awaiting nodeID at %s", endpoint.ToString());

            transport->AddConnection(this);
            if (transport->OnAwaitingNodeID(endpoint))
            {
                Log_Trace();
                transport->DeleteConnection(this);
                return true;
            }
            if (nodeID == UNDEFINED_NODEID)
                Log_Message("[%s] Cluster unknown node connected <=", endpoint.ToString(), nodeID);
            else
                Log_Message("[%s] Cluster node %U connected <=", endpoint.ToString(), nodeID);
            return false;
        }
        
        // both ends have nodeIDs
        msg.Readf("%U:%U:%#R", &clusterID_, &nodeID_, &buffer);
        if (clusterID_ > 0 && clusterID_ != transport->GetClusterID())
        {
            Log_Message("[%R] Cluster invalid configuration, disconnecting...", &buffer);
            transport->DeleteConnection(this);      // drop this
            return true;            
        }
        
        dup = transport->GetConnection(nodeID_);
        if (dup)
        {
            // if the other connections isn't ready yet, drop it
            // OR
            // the other connection is ready
            // in this case, kill the connection that was initiated by higher nodeID
            // in other words, since this is an incoming connection:
            // if nodeID[of initiator] > transport->GetSelfNodeID(): drop

            if (dup->progress != READY || nodeID_ > transport->GetSelfNodeID())
            {
                Log_Trace("delete dup");
                transport->DeleteConnection(dup);       // drop dup
            }
            else if (nodeID_ != transport->GetSelfNodeID())
            {
                Log_Trace("delete this");
                transport->DeleteConnection(this);      // drop this
                return true;
            }
        }
        progress = ClusterConnection::READY;
        nodeID = nodeID_;
        endpoint.Set(buffer);
        Log_Trace("Conn READY to node %U at %s", nodeID, endpoint.ToString());
        if (nodeID != transport->GetSelfNodeID())
        {
            if (nodeID == UNDEFINED_NODEID)
                Log_Message("[%s] Cluster unknown node connected <=", endpoint.ToString());
            else
                Log_Message("[%s] Cluster node %U connected <=", endpoint.ToString(), nodeID);
        }
        
        transport->AddConnection(this);
        transport->OnConnectionReady(nodeID, endpoint);
        transport->OnWriteReadyness(this);
    }
    else if (progress == ClusterConnection::OUTGOING)
        ASSERT_FAIL();
    else
        transport->OnMessage(nodeID, msg); // pass msg to upper layer
    
    return false;
}

void ClusterConnection::OnWriteReadyness()
{
    if (progress != ClusterConnection::READY)
        return;
    
    transport->OnWriteReadyness(this);
}
