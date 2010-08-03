#include "DataNode.h"
#include "System/Common.h"
#include "System/Platform.h"
#include "Framework/Replication/ReplicationManager.h"

#define GET_NAMED_PARAM(params, name, var) \
if (!params.GetNamed(name, sizeof("" name) - 1, var)) { return NULL; }

void DataNode::Init(Table* table_)
{
	table = table_;
	
	if (!table->Get(NULL, "#nodeID", nodeID))
	{
		nodeID = gen_uuid();
		Log_Trace("%" PRIu64, nodeID);
		table->Set(NULL, "#nodeID", nodeID);
	}
	RMAN->SetNodeID(nodeID);
	Log_Trace("nodeID = %" PRIu64, nodeID);
}

bool DataNode::HandleRequest(HttpConn* conn, const HttpRequest& request)
{
	char*		pos;
	char*		qmark;
	unsigned	cmdlen;
	UrlParam	params;

	pos = (char*) request.line.uri;
	if (*pos == '/') 
		pos++;
	
//	pos = ParseType(pos);
	qmark = strchr(pos, '?');
	if (qmark)
	{
		params.Init(qmark + 1, '&');
//		if (type == JSON) 
//			GET_NAMED_OPT_PARAM(params, "callback", jsonCallback);
			
		cmdlen = qmark - pos;
	}
	else
		cmdlen = strlen(pos);

	return ProcessCommand(conn, pos, cmdlen, params);
}

bool DataNode::MatchString(const char* s1, unsigned len1, const char* s2, unsigned len2)
{
	if (len1 != len2)
		return false;
		
	return (strncmp(s1, s2, len2) == 0);
}


#define STR_AND_LEN(s) s, strlen(s)

bool DataNode::ProcessCommand(HttpConn* conn, const char* cmd, unsigned cmdlen, const UrlParam& params)
{
	DataMessage*	msg;
	Buffer			buffer;

	if (MatchString(cmd, cmdlen, STR_AND_LEN("")))
	{
		PrintHello(conn);
		return true;
	}
	
	if (MatchString(cmd, cmdlen, STR_AND_LEN("get"))) 
	{
		ASSERT_FAIL();
	}
	else if (MatchString(cmd, cmdlen, STR_AND_LEN("set")))
	{
//		msg = new DataMessage;
//		msg->ptr = (void*) conn;
//		
//		// TODO: commands
//		// put msg in messages
//		messages.Append(msg);
		ReadBuffer	key;
		ReadBuffer	value;
		
		GET_NAMED_PARAM(params, "key", key);
		GET_NAMED_PARAM(params, "value", value);
		
		buffer.Writef("key: %M\nvalue: %M\n", &key, &value);
		conn->Write(buffer.GetBuffer(), buffer.GetLength());
		conn->Flush(true);
		return true;
	}
	else
		return false;
}

void DataNode::PrintHello(HttpConn* conn)
{
	Buffer			buffer;
	QuorumContext*	context;

	context = RMAN->GetContext(1); // TODO: hack
	
	if (context->IsLeaderKnown())
	{
		buffer.Writef("ChunkID: 1\nPrimary: %U\nSelf: %U\nPaxosID: %U\n", 
		 context->GetLeader(),
		 RMAN->GetNodeID(),
		 context->GetPaxosID());
	}
	else
	{
		buffer.Writef("ChunkID: 1\nNo primary, PaxosID: %U\n", context->GetPaxosID());
	}

	conn->Write(buffer.GetBuffer(), buffer.GetLength());
	conn->Flush(true);
}

void DataNode::OnComplete(DataMessage* msg, bool status)
{
	HttpConn*	conn;
	Buffer		buffer;
	
	assert(msg->type == DATAMESSAGE_SET);
	
	conn = (HttpConn*) msg->ptr;

	if (!status)
		buffer.Write("OK");
	else
		buffer.Write("FAILED");

	conn->Write(buffer.GetBuffer(), buffer.GetLength());
	conn->Flush(true);
	
	messages.Remove(msg);
	delete msg;
}
