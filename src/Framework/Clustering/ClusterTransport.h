#ifndef CLUSTERTRANSPORT_H
#define CLUSTERTRANSPORT_H

#include "Framework/Messaging/Message.h"
#include "ClusterServer.h"

class ClusterTransport
{
public:
	virtual ~ClusterTransport() {}
	
	void						Init(uint64_t nodeID, Endpoint& endpoint);
	
	uint64_t					GetSelfNodeID();
	Endpoint&					GetSelfEndpoint();

	void						AddEndpoint(uint64_t nodeID, Endpoint& endpoint);
	bool						SetNodeID(Endpoint& endpoint, uint64_t nodeID);
	
	void						SendMessage(uint64_t nodeID, Buffer& prefix, Message& msg);
	void						SendPriorityMessage(uint64_t nodeID, Buffer& prefix, Message& msg);
	
	void						DropConnection(uint64_t nodeID);
	void						DropConnection(Endpoint endpoint);
	
	virtual void				OnConnectionReady(uint64_t nodeID, Endpoint endpoint)			= 0;
	virtual void				OnAwaitingNodeID(Endpoint endpoint)								= 0;
	virtual void				OnMessage(uint64_t nodeID, ReadBuffer msg)						= 0;

private:
	// for ClusterConnection:
	void						AddConnection(ClusterConnection* conn);
	ClusterConnection*			GetConnection(uint64_t nodeID);
	ClusterConnection*			GetConnection(Endpoint& endpoint);
	void						DeleteConnection(ClusterConnection* conn);

	uint64_t					nodeID;
	Endpoint					endpoint;
	Buffer						msgBuffer;
	ClusterServer				server;
	InList<ClusterConnection>	conns;

	friend class ClusterConnection;
};

#endif