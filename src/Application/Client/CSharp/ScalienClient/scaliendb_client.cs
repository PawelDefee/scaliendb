/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace Scalien {

using System;
using System.Runtime.InteropServices;

public class scaliendb_client {
  public static long imaxabs(long n) {
    long ret = scaliendb_clientPINVOKE.imaxabs(n);
    return ret;
  }

  public static imaxdiv_t imaxdiv(long numer, long denom) {
    imaxdiv_t ret = new imaxdiv_t(scaliendb_clientPINVOKE.imaxdiv(numer, denom), true);
    return ret;
  }

  public static long strtoimax(string nptr, SWIGTYPE_p_p_char endptr, int arg2) {
    long ret = scaliendb_clientPINVOKE.strtoimax(nptr, SWIGTYPE_p_p_char.getCPtr(endptr), arg2);
    return ret;
  }

  public static ulong strtoumax(string nptr, SWIGTYPE_p_p_char endptr, int arg2) {
    ulong ret = scaliendb_clientPINVOKE.strtoumax(nptr, SWIGTYPE_p_p_char.getCPtr(endptr), arg2);
    return ret;
  }

  public unsafe static void SDBP_ResultClose(SWIGTYPE_p_void result) {
    scaliendb_clientPINVOKE.SDBP_ResultClose(SWIGTYPE_p_void.getCPtr(result));
  }

  public unsafe static string SDBP_ResultKey(SWIGTYPE_p_void result) {
    string ret = scaliendb_clientPINVOKE.SDBP_ResultKey(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static string SDBP_ResultValue(SWIGTYPE_p_void result) {
    string ret = scaliendb_clientPINVOKE.SDBP_ResultValue(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static SDBP_Buffer SDBP_ResultKeyBuffer(SWIGTYPE_p_void result) {
    SDBP_Buffer ret = new SDBP_Buffer(scaliendb_clientPINVOKE.SDBP_ResultKeyBuffer(SWIGTYPE_p_void.getCPtr(result)), true);
    return ret;
  }

  public unsafe static SDBP_Buffer SDBP_ResultValueBuffer(SWIGTYPE_p_void result) {
    SDBP_Buffer ret = new SDBP_Buffer(scaliendb_clientPINVOKE.SDBP_ResultValueBuffer(SWIGTYPE_p_void.getCPtr(result)), true);
    return ret;
  }

  public unsafe static long SDBP_ResultSignedNumber(SWIGTYPE_p_void result) {
    long ret = scaliendb_clientPINVOKE.SDBP_ResultSignedNumber(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static ulong SDBP_ResultNumber(SWIGTYPE_p_void result) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_ResultNumber(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static bool SDBP_ResultIsConditionalSuccess(SWIGTYPE_p_void result) {
    bool ret = scaliendb_clientPINVOKE.SDBP_ResultIsConditionalSuccess(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static ulong SDBP_ResultDatabaseID(SWIGTYPE_p_void result) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_ResultDatabaseID(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static ulong SDBP_ResultTableID(SWIGTYPE_p_void result) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_ResultTableID(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static void SDBP_ResultBegin(SWIGTYPE_p_void result) {
    scaliendb_clientPINVOKE.SDBP_ResultBegin(SWIGTYPE_p_void.getCPtr(result));
  }

  public unsafe static void SDBP_ResultNext(SWIGTYPE_p_void result) {
    scaliendb_clientPINVOKE.SDBP_ResultNext(SWIGTYPE_p_void.getCPtr(result));
  }

  public unsafe static bool SDBP_ResultIsEnd(SWIGTYPE_p_void result) {
    bool ret = scaliendb_clientPINVOKE.SDBP_ResultIsEnd(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static bool SDBP_ResultIsFinished(SWIGTYPE_p_void result) {
    bool ret = scaliendb_clientPINVOKE.SDBP_ResultIsFinished(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static int SDBP_ResultTransportStatus(SWIGTYPE_p_void result) {
    int ret = scaliendb_clientPINVOKE.SDBP_ResultTransportStatus(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static int SDBP_ResultCommandStatus(SWIGTYPE_p_void result) {
    int ret = scaliendb_clientPINVOKE.SDBP_ResultCommandStatus(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static uint SDBP_ResultNumNodes(SWIGTYPE_p_void result) {
    uint ret = scaliendb_clientPINVOKE.SDBP_ResultNumNodes(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static ulong SDBP_ResultNodeID(SWIGTYPE_p_void result, uint n) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_ResultNodeID(SWIGTYPE_p_void.getCPtr(result), n);
    return ret;
  }

  public unsafe static uint SDBP_ResultElapsedTime(SWIGTYPE_p_void result) {
    uint ret = scaliendb_clientPINVOKE.SDBP_ResultElapsedTime(SWIGTYPE_p_void.getCPtr(result));
    return ret;
  }

  public unsafe static SWIGTYPE_p_void SDBP_Create() {
    IntPtr cPtr = scaliendb_clientPINVOKE.SDBP_Create();
    SWIGTYPE_p_void ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_void(cPtr, false);
    return ret;
  }

  public unsafe static int SDBP_Init(SWIGTYPE_p_void client, SDBP_NodeParams arg1) {
    int ret = scaliendb_clientPINVOKE.SDBP_Init(SWIGTYPE_p_void.getCPtr(client), SDBP_NodeParams.getCPtr(arg1));
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static void SDBP_Destroy(SWIGTYPE_p_void client) {
    scaliendb_clientPINVOKE.SDBP_Destroy(SWIGTYPE_p_void.getCPtr(client));
  }

  public unsafe static SWIGTYPE_p_void SDBP_GetResult(SWIGTYPE_p_void client) {
    IntPtr cPtr = scaliendb_clientPINVOKE.SDBP_GetResult(SWIGTYPE_p_void.getCPtr(client));
    SWIGTYPE_p_void ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_void(cPtr, false);
    return ret;
  }

  public unsafe static void SDBP_SetGlobalTimeout(SWIGTYPE_p_void client, ulong timeout) {
    scaliendb_clientPINVOKE.SDBP_SetGlobalTimeout(SWIGTYPE_p_void.getCPtr(client), timeout);
  }

  public unsafe static void SDBP_SetMasterTimeout(SWIGTYPE_p_void client, ulong timeout) {
    scaliendb_clientPINVOKE.SDBP_SetMasterTimeout(SWIGTYPE_p_void.getCPtr(client), timeout);
  }

  public unsafe static ulong SDBP_GetGlobalTimeout(SWIGTYPE_p_void client) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_GetGlobalTimeout(SWIGTYPE_p_void.getCPtr(client));
    return ret;
  }

  public unsafe static ulong SDBP_GetMasterTimeout(SWIGTYPE_p_void client) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_GetMasterTimeout(SWIGTYPE_p_void.getCPtr(client));
    return ret;
  }

  public unsafe static string SDBP_GetJSONConfigState(SWIGTYPE_p_void client) {
    string ret = scaliendb_clientPINVOKE.SDBP_GetJSONConfigState(SWIGTYPE_p_void.getCPtr(client));
    return ret;
  }

  public unsafe static void SDBP_WaitConfigState(SWIGTYPE_p_void client) {
    scaliendb_clientPINVOKE.SDBP_WaitConfigState(SWIGTYPE_p_void.getCPtr(client));
  }

  public unsafe static void SDBP_SetConsistencyMode(SWIGTYPE_p_void client, int consistencyMode) {
    scaliendb_clientPINVOKE.SDBP_SetConsistencyMode(SWIGTYPE_p_void.getCPtr(client), consistencyMode);
  }

  public unsafe static void SDBP_SetBatchMode(SWIGTYPE_p_void client, int batchMode) {
    scaliendb_clientPINVOKE.SDBP_SetBatchMode(SWIGTYPE_p_void.getCPtr(client), batchMode);
  }

  public unsafe static void SDBP_SetBatchLimit(SWIGTYPE_p_void client, uint batchLimit) {
    scaliendb_clientPINVOKE.SDBP_SetBatchLimit(SWIGTYPE_p_void.getCPtr(client), batchLimit);
  }

  public unsafe static int SDBP_CreateDatabase(SWIGTYPE_p_void client, string name) {
    int ret = scaliendb_clientPINVOKE.SDBP_CreateDatabase(SWIGTYPE_p_void.getCPtr(client), name);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_RenameDatabase(SWIGTYPE_p_void client, ulong databaseID, string name) {
    int ret = scaliendb_clientPINVOKE.SDBP_RenameDatabase(SWIGTYPE_p_void.getCPtr(client), databaseID, name);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_DeleteDatabase(SWIGTYPE_p_void client, ulong databaseID) {
    int ret = scaliendb_clientPINVOKE.SDBP_DeleteDatabase(SWIGTYPE_p_void.getCPtr(client), databaseID);
    return ret;
  }

  public unsafe static int SDBP_CreateTable(SWIGTYPE_p_void client, ulong databaseID, ulong quorumID, string name) {
    int ret = scaliendb_clientPINVOKE.SDBP_CreateTable(SWIGTYPE_p_void.getCPtr(client), databaseID, quorumID, name);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_RenameTable(SWIGTYPE_p_void client, ulong tableID, string name) {
    int ret = scaliendb_clientPINVOKE.SDBP_RenameTable(SWIGTYPE_p_void.getCPtr(client), tableID, name);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_DeleteTable(SWIGTYPE_p_void client, ulong tableID) {
    int ret = scaliendb_clientPINVOKE.SDBP_DeleteTable(SWIGTYPE_p_void.getCPtr(client), tableID);
    return ret;
  }

  public unsafe static int SDBP_TruncateTable(SWIGTYPE_p_void client, ulong tableID) {
    int ret = scaliendb_clientPINVOKE.SDBP_TruncateTable(SWIGTYPE_p_void.getCPtr(client), tableID);
    return ret;
  }

  public unsafe static uint SDBP_GetNumQuorums(SWIGTYPE_p_void client) {
    uint ret = scaliendb_clientPINVOKE.SDBP_GetNumQuorums(SWIGTYPE_p_void.getCPtr(client));
    return ret;
  }

  public unsafe static ulong SDBP_GetQuorumIDAt(SWIGTYPE_p_void client, uint n) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_GetQuorumIDAt(SWIGTYPE_p_void.getCPtr(client), n);
    return ret;
  }

  public unsafe static string SDBP_GetQuorumNameAt(SWIGTYPE_p_void client, uint n) {
    string ret = scaliendb_clientPINVOKE.SDBP_GetQuorumNameAt(SWIGTYPE_p_void.getCPtr(client), n);
    return ret;
  }

  public unsafe static ulong SDBP_GetQuorumIDByName(SWIGTYPE_p_void client, string name) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_GetQuorumIDByName(SWIGTYPE_p_void.getCPtr(client), name);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static uint SDBP_GetNumDatabases(SWIGTYPE_p_void client) {
    uint ret = scaliendb_clientPINVOKE.SDBP_GetNumDatabases(SWIGTYPE_p_void.getCPtr(client));
    return ret;
  }

  public unsafe static ulong SDBP_GetDatabaseIDAt(SWIGTYPE_p_void client, uint n) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_GetDatabaseIDAt(SWIGTYPE_p_void.getCPtr(client), n);
    return ret;
  }

  public unsafe static string SDBP_GetDatabaseNameAt(SWIGTYPE_p_void client, uint n) {
    string ret = scaliendb_clientPINVOKE.SDBP_GetDatabaseNameAt(SWIGTYPE_p_void.getCPtr(client), n);
    return ret;
  }

  public unsafe static ulong SDBP_GetDatabaseIDByName(SWIGTYPE_p_void client, string name) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_GetDatabaseIDByName(SWIGTYPE_p_void.getCPtr(client), name);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static uint SDBP_GetNumTables(SWIGTYPE_p_void client, ulong databaseID) {
    uint ret = scaliendb_clientPINVOKE.SDBP_GetNumTables(SWIGTYPE_p_void.getCPtr(client), databaseID);
    return ret;
  }

  public unsafe static ulong SDBP_GetTableIDAt(SWIGTYPE_p_void client, ulong databaseID, uint n) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_GetTableIDAt(SWIGTYPE_p_void.getCPtr(client), databaseID, n);
    return ret;
  }

  public unsafe static string SDBP_GetTableNameAt(SWIGTYPE_p_void client, ulong databaseID, uint n) {
    string ret = scaliendb_clientPINVOKE.SDBP_GetTableNameAt(SWIGTYPE_p_void.getCPtr(client), databaseID, n);
    return ret;
  }

  public unsafe static ulong SDBP_GetTableIDByName(SWIGTYPE_p_void client, ulong databaseID, string name) {
    ulong ret = scaliendb_clientPINVOKE.SDBP_GetTableIDByName(SWIGTYPE_p_void.getCPtr(client), databaseID, name);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_Get(SWIGTYPE_p_void client, ulong tableID, string key) {
    int ret = scaliendb_clientPINVOKE.SDBP_Get(SWIGTYPE_p_void.getCPtr(client), tableID, key);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_GetCStr(SWIGTYPE_p_void client, ulong tableID, IntPtr key, int len) {
    int ret = scaliendb_clientPINVOKE.SDBP_GetCStr(SWIGTYPE_p_void.getCPtr(client), tableID, key, len);
    return ret;
  }

  public unsafe static int SDBP_Set(SWIGTYPE_p_void client, ulong tableID, string key, string value) {
    int ret = scaliendb_clientPINVOKE.SDBP_Set(SWIGTYPE_p_void.getCPtr(client), tableID, key, value);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_SetCStr(SWIGTYPE_p_void client_, ulong tableID, IntPtr key, int lenKey, IntPtr value, int lenValue) {
    int ret = scaliendb_clientPINVOKE.SDBP_SetCStr(SWIGTYPE_p_void.getCPtr(client_), tableID, key, lenKey, value, lenValue);
    return ret;
  }

  public unsafe static int SDBP_Add(SWIGTYPE_p_void client, ulong tableID, string key, long number) {
    int ret = scaliendb_clientPINVOKE.SDBP_Add(SWIGTYPE_p_void.getCPtr(client), tableID, key, number);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_AddCStr(SWIGTYPE_p_void client_, ulong tableID, IntPtr key, int len, long number) {
    int ret = scaliendb_clientPINVOKE.SDBP_AddCStr(SWIGTYPE_p_void.getCPtr(client_), tableID, key, len, number);
    return ret;
  }

  public unsafe static int SDBP_Delete(SWIGTYPE_p_void client, ulong tableID, string key) {
    int ret = scaliendb_clientPINVOKE.SDBP_Delete(SWIGTYPE_p_void.getCPtr(client), tableID, key);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_DeleteCStr(SWIGTYPE_p_void client_, ulong tableID, IntPtr key, int len) {
    int ret = scaliendb_clientPINVOKE.SDBP_DeleteCStr(SWIGTYPE_p_void.getCPtr(client_), tableID, key, len);
    return ret;
  }

  public unsafe static int SDBP_SequenceSet(SWIGTYPE_p_void client, ulong tableID, string key, ulong number) {
    int ret = scaliendb_clientPINVOKE.SDBP_SequenceSet(SWIGTYPE_p_void.getCPtr(client), tableID, key, number);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_SequenceSetCStr(SWIGTYPE_p_void client_, ulong tableID, IntPtr key, int len, ulong number) {
    int ret = scaliendb_clientPINVOKE.SDBP_SequenceSetCStr(SWIGTYPE_p_void.getCPtr(client_), tableID, key, len, number);
    return ret;
  }

  public unsafe static int SDBP_SequenceNext(SWIGTYPE_p_void client, ulong tableID, string key) {
    int ret = scaliendb_clientPINVOKE.SDBP_SequenceNext(SWIGTYPE_p_void.getCPtr(client), tableID, key);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_SequenceNextCStr(SWIGTYPE_p_void client, ulong tableID, IntPtr key, int len) {
    int ret = scaliendb_clientPINVOKE.SDBP_SequenceNextCStr(SWIGTYPE_p_void.getCPtr(client), tableID, key, len);
    return ret;
  }

  public unsafe static int SDBP_ListKeys(SWIGTYPE_p_void client, ulong tableID, string startKey, string endKey, string prefix, uint count, bool forwardDirection, bool skip) {
    int ret = scaliendb_clientPINVOKE.SDBP_ListKeys(SWIGTYPE_p_void.getCPtr(client), tableID, startKey, endKey, prefix, count, forwardDirection, skip);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_ListKeysCStr(SWIGTYPE_p_void client, ulong tableID, IntPtr startKey, int startKeyLen, IntPtr endKey, int endKeyLen, IntPtr prefix, int prefixLen, uint count, bool forwardDirection, bool skip) {
    int ret = scaliendb_clientPINVOKE.SDBP_ListKeysCStr(SWIGTYPE_p_void.getCPtr(client), tableID, startKey, startKeyLen, endKey, endKeyLen, prefix, prefixLen, count, forwardDirection, skip);
    return ret;
  }

  public unsafe static int SDBP_ListKeyValues(SWIGTYPE_p_void client, ulong tableID, string startKey, string endKey, string prefix, uint count, bool forwardDirection, bool skip) {
    int ret = scaliendb_clientPINVOKE.SDBP_ListKeyValues(SWIGTYPE_p_void.getCPtr(client), tableID, startKey, endKey, prefix, count, forwardDirection, skip);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_ListKeyValuesCStr(SWIGTYPE_p_void client, ulong tableID, IntPtr startKey, int startKeyLen, IntPtr endKey, int endKeyLen, IntPtr prefix, int prefixLen, uint count, bool forwardDirection, bool skip) {
    int ret = scaliendb_clientPINVOKE.SDBP_ListKeyValuesCStr(SWIGTYPE_p_void.getCPtr(client), tableID, startKey, startKeyLen, endKey, endKeyLen, prefix, prefixLen, count, forwardDirection, skip);
    return ret;
  }

  public unsafe static int SDBP_Count(SWIGTYPE_p_void client, ulong tableID, string startKey, string endKey, string prefix, bool forwardDirection) {
    int ret = scaliendb_clientPINVOKE.SDBP_Count(SWIGTYPE_p_void.getCPtr(client), tableID, startKey, endKey, prefix, forwardDirection);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public unsafe static int SDBP_CountCStr(SWIGTYPE_p_void client, ulong tableID, IntPtr startKey, int startKeyLen, IntPtr endKey, int endKeyLen, IntPtr prefix, int prefixLen, bool forwardDirection) {
    int ret = scaliendb_clientPINVOKE.SDBP_CountCStr(SWIGTYPE_p_void.getCPtr(client), tableID, startKey, startKeyLen, endKey, endKeyLen, prefix, prefixLen, forwardDirection);
    return ret;
  }

  public unsafe static int SDBP_Begin(SWIGTYPE_p_void client) {
    int ret = scaliendb_clientPINVOKE.SDBP_Begin(SWIGTYPE_p_void.getCPtr(client));
    return ret;
  }

  public unsafe static int SDBP_Submit(SWIGTYPE_p_void client) {
    int ret = scaliendb_clientPINVOKE.SDBP_Submit(SWIGTYPE_p_void.getCPtr(client));
    return ret;
  }

  public unsafe static int SDBP_Cancel(SWIGTYPE_p_void client) {
    int ret = scaliendb_clientPINVOKE.SDBP_Cancel(SWIGTYPE_p_void.getCPtr(client));
    return ret;
  }

  public unsafe static void SDBP_SetTrace(bool trace) {
    scaliendb_clientPINVOKE.SDBP_SetTrace(trace);
  }

  public unsafe static void SDBP_SetLogFile(string filename) {
    scaliendb_clientPINVOKE.SDBP_SetLogFile(filename);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
  }

  public unsafe static void SDBP_SetTraceBufferSize(uint traceBufferSize) {
    scaliendb_clientPINVOKE.SDBP_SetTraceBufferSize(traceBufferSize);
  }

  public unsafe static void SDBP_LogTrace(string msg) {
    scaliendb_clientPINVOKE.SDBP_LogTrace(msg);
    if (scaliendb_clientPINVOKE.SWIGPendingException.Pending) throw scaliendb_clientPINVOKE.SWIGPendingException.Retrieve();
  }

  public unsafe static void SDBP_SetShardPoolSize(uint shardPoolSize) {
    scaliendb_clientPINVOKE.SDBP_SetShardPoolSize(shardPoolSize);
  }

  public unsafe static string SDBP_GetVersion() {
    string ret = scaliendb_clientPINVOKE.SDBP_GetVersion();
    return ret;
  }

  public unsafe static string SDBP_GetDebugString() {
    string ret = scaliendb_clientPINVOKE.SDBP_GetDebugString();
    return ret;
  }

}

}
