#include "ClientResponse.h"
#include "System/Buffers/Buffer.h"

ClientResponse::ClientResponse()
{
    valueBuffer = NULL;
    keys = NULL;
    values = NULL;
    type = CLIENTRESPONSE_NORESPONSE;
}

ClientResponse::~ClientResponse()
{
    delete valueBuffer;
    delete[] keys;
    delete[] values;
}

void ClientResponse::CopyValue()
{
    if (valueBuffer == NULL)
        valueBuffer = new Buffer;

    valueBuffer->Write(value.GetBuffer(), value.GetLength());
    value.Wrap(*valueBuffer);
}

void ClientResponse::Transfer(ClientResponse& other)
{
    other.type = type;
    other.number = number;
    other.commandID = commandID;
    other.value = value;
    other.valueBuffer = valueBuffer;
    other.configState = configState;
    other.numKeys = numKeys;
    other.keys = keys;
    other.values = values;
    
    valueBuffer = NULL;
}

bool ClientResponse::OK()
{
    type = CLIENTRESPONSE_OK;
    return true;
}

bool ClientResponse::Number(uint64_t number_)
{
    type = CLIENTRESPONSE_NUMBER;
    number = number_;
    return true;
}

bool ClientResponse::Value(ReadBuffer& value_)
{
    type = CLIENTRESPONSE_VALUE;
    value = value_;
    return true;
}

bool ClientResponse::ListKeys(unsigned numKeys_, ReadBuffer* keys_)
{
    unsigned    i;
    
    type = CLIENTRESPONSE_LIST_KEYS;
    numKeys = numKeys_;
    keys = new ReadBuffer[numKeys];
    for (i = 0; i < numKeys; i++)
        keys[i] = keys_[i];
    
    return true;
}

bool ClientResponse::ListKeyValues(unsigned numKeys_, ReadBuffer* keys_, ReadBuffer* values_)
{
    unsigned    i;
    
    type = CLIENTRESPONSE_LIST_KEYVALUES;
    numKeys = numKeys_;
    keys = new ReadBuffer[numKeys];
    values = new ReadBuffer[numKeys];
    for (i = 0; i < numKeys; i++)
    {
        keys[i] = keys_[i];
        values[i] = values_[i];
    }
    
    return true;
}

bool ClientResponse::ConfigStateResponse(ConfigState& configState_)
{
    type = CLIENTRESPONSE_CONFIG_STATE;
    configState = configState_;
    return true;
}

bool ClientResponse::NoService()
{
    type = CLIENTRESPONSE_NOSERVICE;
    return true;
}

bool ClientResponse::Failed()
{
    type = CLIENTRESPONSE_FAILED;
    return true;
}

bool ClientResponse::NoResponse()
{
    type = CLIENTRESPONSE_NORESPONSE;
    return true;
}
