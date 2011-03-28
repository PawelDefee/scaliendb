/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.scalien.scaliendb;

public class scaliendb_client {
  public static long imaxabs(long n) {
    return scaliendb_clientJNI.imaxabs(n);
  }

  public static imaxdiv_t imaxdiv(long numer, long denom) {
    return new imaxdiv_t(scaliendb_clientJNI.imaxdiv(numer, denom), true);
  }

  public static long strtoimax(String nptr, SWIGTYPE_p_p_char endptr, int base) {
    return scaliendb_clientJNI.strtoimax(nptr, SWIGTYPE_p_p_char.getCPtr(endptr), base);
  }

  public static java.math.BigInteger strtoumax(String nptr, SWIGTYPE_p_p_char endptr, int base) {
    return scaliendb_clientJNI.strtoumax(nptr, SWIGTYPE_p_p_char.getCPtr(endptr), base);
  }

  public static void SDBP_ResultClose(SWIGTYPE_p_void result) {
    scaliendb_clientJNI.SDBP_ResultClose(SWIGTYPE_p_void.getCPtr(result));
  }

  public static String SDBP_ResultKey(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultKey(SWIGTYPE_p_void.getCPtr(result));
  }

  public static String SDBP_ResultValue(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultValue(SWIGTYPE_p_void.getCPtr(result));
  }

  public static byte[] SDBP_ResultKeyBuffer(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultKeyBuffer(SWIGTYPE_p_void.getCPtr(result));
}

  public static byte[] SDBP_ResultValueBuffer(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultValueBuffer(SWIGTYPE_p_void.getCPtr(result));
}

  public static java.math.BigInteger SDBP_ResultNumber(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultNumber(SWIGTYPE_p_void.getCPtr(result));
  }

  public static java.math.BigInteger SDBP_ResultDatabaseID(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultDatabaseID(SWIGTYPE_p_void.getCPtr(result));
  }

  public static java.math.BigInteger SDBP_ResultTableID(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultTableID(SWIGTYPE_p_void.getCPtr(result));
  }

  public static void SDBP_ResultBegin(SWIGTYPE_p_void result) {
    scaliendb_clientJNI.SDBP_ResultBegin(SWIGTYPE_p_void.getCPtr(result));
  }

  public static void SDBP_ResultNext(SWIGTYPE_p_void result) {
    scaliendb_clientJNI.SDBP_ResultNext(SWIGTYPE_p_void.getCPtr(result));
  }

  public static boolean SDBP_ResultIsEnd(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultIsEnd(SWIGTYPE_p_void.getCPtr(result));
  }

  public static int SDBP_ResultTransportStatus(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultTransportStatus(SWIGTYPE_p_void.getCPtr(result));
  }

  public static int SDBP_ResultCommandStatus(SWIGTYPE_p_void result) {
    return scaliendb_clientJNI.SDBP_ResultCommandStatus(SWIGTYPE_p_void.getCPtr(result));
  }

  public static SWIGTYPE_p_void SDBP_Create() {
    long cPtr = scaliendb_clientJNI.SDBP_Create();
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public static int SDBP_Init(SWIGTYPE_p_void client, SDBP_NodeParams params) {
    return scaliendb_clientJNI.SDBP_Init(SWIGTYPE_p_void.getCPtr(client), SDBP_NodeParams.getCPtr(params), params);
  }

  public static void SDBP_Destroy(SWIGTYPE_p_void client) {
    scaliendb_clientJNI.SDBP_Destroy(SWIGTYPE_p_void.getCPtr(client));
  }

  public static SWIGTYPE_p_void SDBP_GetResult(SWIGTYPE_p_void client) {
    long cPtr = scaliendb_clientJNI.SDBP_GetResult(SWIGTYPE_p_void.getCPtr(client));
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public static void SDBP_SetGlobalTimeout(SWIGTYPE_p_void client, java.math.BigInteger timeout) {
    scaliendb_clientJNI.SDBP_SetGlobalTimeout(SWIGTYPE_p_void.getCPtr(client), timeout);
  }

  public static void SDBP_SetMasterTimeout(SWIGTYPE_p_void client, java.math.BigInteger timeout) {
    scaliendb_clientJNI.SDBP_SetMasterTimeout(SWIGTYPE_p_void.getCPtr(client), timeout);
  }

  public static java.math.BigInteger SDBP_GetGlobalTimeout(SWIGTYPE_p_void client) {
    return scaliendb_clientJNI.SDBP_GetGlobalTimeout(SWIGTYPE_p_void.getCPtr(client));
  }

  public static java.math.BigInteger SDBP_GetMasterTimeout(SWIGTYPE_p_void client) {
    return scaliendb_clientJNI.SDBP_GetMasterTimeout(SWIGTYPE_p_void.getCPtr(client));
  }

  public static java.math.BigInteger SDBP_GetCurrentDatabaseID(SWIGTYPE_p_void client) {
    return scaliendb_clientJNI.SDBP_GetCurrentDatabaseID(SWIGTYPE_p_void.getCPtr(client));
  }

  public static java.math.BigInteger SDBP_GetCurrentTableID(SWIGTYPE_p_void client) {
    return scaliendb_clientJNI.SDBP_GetCurrentTableID(SWIGTYPE_p_void.getCPtr(client));
  }

  public static void SDBP_SetBatchLimit(SWIGTYPE_p_void client, java.math.BigInteger limit) {
    scaliendb_clientJNI.SDBP_SetBatchLimit(SWIGTYPE_p_void.getCPtr(client), limit);
  }

  public static void SDBP_SetBulkLoading(SWIGTYPE_p_void client, boolean bulk) {
    scaliendb_clientJNI.SDBP_SetBulkLoading(SWIGTYPE_p_void.getCPtr(client), bulk);
  }

  public static int SDBP_CreateQuorum(SWIGTYPE_p_void client, SDBP_NodeParams params) {
    return scaliendb_clientJNI.SDBP_CreateQuorum(SWIGTYPE_p_void.getCPtr(client), SDBP_NodeParams.getCPtr(params), params);
  }

  public static int SDBP_DeleteQuorum(SWIGTYPE_p_void client, java.math.BigInteger quorumID) {
    return scaliendb_clientJNI.SDBP_DeleteQuorum(SWIGTYPE_p_void.getCPtr(client), quorumID);
  }

  public static int SDBP_AddNode(SWIGTYPE_p_void client, java.math.BigInteger quorumID, java.math.BigInteger nodeID) {
    return scaliendb_clientJNI.SDBP_AddNode(SWIGTYPE_p_void.getCPtr(client), quorumID, nodeID);
  }

  public static int SDBP_RemoveNode(SWIGTYPE_p_void client, java.math.BigInteger quorumID, java.math.BigInteger nodeID) {
    return scaliendb_clientJNI.SDBP_RemoveNode(SWIGTYPE_p_void.getCPtr(client), quorumID, nodeID);
  }

  public static int SDBP_ActivateNode(SWIGTYPE_p_void client, java.math.BigInteger nodeID) {
    return scaliendb_clientJNI.SDBP_ActivateNode(SWIGTYPE_p_void.getCPtr(client), nodeID);
  }

  public static int SDBP_CreateDatabase(SWIGTYPE_p_void client, String name) {
    return scaliendb_clientJNI.SDBP_CreateDatabase(SWIGTYPE_p_void.getCPtr(client), name);
  }

  public static int SDBP_RenameDatabase(SWIGTYPE_p_void client, java.math.BigInteger databaseID, String name) {
    return scaliendb_clientJNI.SDBP_RenameDatabase(SWIGTYPE_p_void.getCPtr(client), databaseID, name);
  }

  public static int SDBP_DeleteDatabase(SWIGTYPE_p_void client, java.math.BigInteger databaseID) {
    return scaliendb_clientJNI.SDBP_DeleteDatabase(SWIGTYPE_p_void.getCPtr(client), databaseID);
  }

  public static int SDBP_CreateTable(SWIGTYPE_p_void client, java.math.BigInteger databaseID, java.math.BigInteger quorumID, String name) {
    return scaliendb_clientJNI.SDBP_CreateTable(SWIGTYPE_p_void.getCPtr(client), databaseID, quorumID, name);
  }

  public static int SDBP_RenameTable(SWIGTYPE_p_void client, java.math.BigInteger tableID, String name) {
    return scaliendb_clientJNI.SDBP_RenameTable(SWIGTYPE_p_void.getCPtr(client), tableID, name);
  }

  public static int SDBP_DeleteTable(SWIGTYPE_p_void client, java.math.BigInteger tableID) {
    return scaliendb_clientJNI.SDBP_DeleteTable(SWIGTYPE_p_void.getCPtr(client), tableID);
  }

  public static int SDBP_TruncateTable(SWIGTYPE_p_void client, java.math.BigInteger tableID) {
    return scaliendb_clientJNI.SDBP_TruncateTable(SWIGTYPE_p_void.getCPtr(client), tableID);
  }

  public static java.math.BigInteger SDBP_GetDatabaseID(SWIGTYPE_p_void client, String name) {
    return scaliendb_clientJNI.SDBP_GetDatabaseID(SWIGTYPE_p_void.getCPtr(client), name);
  }

  public static java.math.BigInteger SDBP_GetTableID(SWIGTYPE_p_void client, java.math.BigInteger databaseID, String name) {
    return scaliendb_clientJNI.SDBP_GetTableID(SWIGTYPE_p_void.getCPtr(client), databaseID, name);
  }

  public static int SDBP_UseDatabase(SWIGTYPE_p_void client, String name) {
    return scaliendb_clientJNI.SDBP_UseDatabase(SWIGTYPE_p_void.getCPtr(client), name);
  }

  public static int SDBP_UseTable(SWIGTYPE_p_void client, String name) {
    return scaliendb_clientJNI.SDBP_UseTable(SWIGTYPE_p_void.getCPtr(client), name);
  }

  public static int SDBP_Get(SWIGTYPE_p_void client, String key) {
    return scaliendb_clientJNI.SDBP_Get(SWIGTYPE_p_void.getCPtr(client), key);
  }

  public static int SDBP_GetCStr(SWIGTYPE_p_void client, byte[] key, int len) {
    return scaliendb_clientJNI.SDBP_GetCStr(SWIGTYPE_p_void.getCPtr(client), key, len);
  }

  public static int SDBP_Set(SWIGTYPE_p_void client, String key, String value) {
    return scaliendb_clientJNI.SDBP_Set(SWIGTYPE_p_void.getCPtr(client), key, value);
  }

  public static int SDBP_SetCStr(SWIGTYPE_p_void client_, byte[] key, int lenKey, byte[] value, int lenValue) {
    return scaliendb_clientJNI.SDBP_SetCStr(SWIGTYPE_p_void.getCPtr(client_), key, lenKey, value, lenValue);
  }

  public static int SDBP_SetIfNotExists(SWIGTYPE_p_void client, String key, String value) {
    return scaliendb_clientJNI.SDBP_SetIfNotExists(SWIGTYPE_p_void.getCPtr(client), key, value);
  }

  public static int SDBP_SetIfNotExistsCStr(SWIGTYPE_p_void client, byte[] key, int lenKey, byte[] value, int lenValue) {
    return scaliendb_clientJNI.SDBP_SetIfNotExistsCStr(SWIGTYPE_p_void.getCPtr(client), key, lenKey, value, lenValue);
  }

  public static int SDBP_TestAndSet(SWIGTYPE_p_void client, String key, String test, String value) {
    return scaliendb_clientJNI.SDBP_TestAndSet(SWIGTYPE_p_void.getCPtr(client), key, test, value);
  }

  public static int SDBP_TestAndSetCStr(SWIGTYPE_p_void client, byte[] key, int lenKey, byte[] test, int lenTest, byte[] value, int lenValue) {
    return scaliendb_clientJNI.SDBP_TestAndSetCStr(SWIGTYPE_p_void.getCPtr(client), key, lenKey, test, lenTest, value, lenValue);
  }

  public static int SDBP_GetAndSet(SWIGTYPE_p_void client, String key, String value) {
    return scaliendb_clientJNI.SDBP_GetAndSet(SWIGTYPE_p_void.getCPtr(client), key, value);
  }

  public static int SDBP_GetAndSetCStr(SWIGTYPE_p_void client, byte[] key, int lenKey, byte[] value, int lenValue) {
    return scaliendb_clientJNI.SDBP_GetAndSetCStr(SWIGTYPE_p_void.getCPtr(client), key, lenKey, value, lenValue);
  }

  public static int SDBP_Add(SWIGTYPE_p_void client, String key, long number) {
    return scaliendb_clientJNI.SDBP_Add(SWIGTYPE_p_void.getCPtr(client), key, number);
  }

  public static int SDBP_AddCStr(SWIGTYPE_p_void client_, byte[] key, int len, long number) {
    return scaliendb_clientJNI.SDBP_AddCStr(SWIGTYPE_p_void.getCPtr(client_), key, len, number);
  }

  public static int SDBP_Append(SWIGTYPE_p_void client, String key, String value) {
    return scaliendb_clientJNI.SDBP_Append(SWIGTYPE_p_void.getCPtr(client), key, value);
  }

  public static int SDBP_AppendCStr(SWIGTYPE_p_void client_, byte[] key, int lenKey, byte[] value, int lenValue) {
    return scaliendb_clientJNI.SDBP_AppendCStr(SWIGTYPE_p_void.getCPtr(client_), key, lenKey, value, lenValue);
  }

  public static int SDBP_Delete(SWIGTYPE_p_void client, String key) {
    return scaliendb_clientJNI.SDBP_Delete(SWIGTYPE_p_void.getCPtr(client), key);
  }

  public static int SDBP_DeleteCStr(SWIGTYPE_p_void client_, byte[] key, int len) {
    return scaliendb_clientJNI.SDBP_DeleteCStr(SWIGTYPE_p_void.getCPtr(client_), key, len);
  }

  public static int SDBP_Remove(SWIGTYPE_p_void client, String key) {
    return scaliendb_clientJNI.SDBP_Remove(SWIGTYPE_p_void.getCPtr(client), key);
  }

  public static int SDBP_RemoveCStr(SWIGTYPE_p_void client_, byte[] key, int len) {
    return scaliendb_clientJNI.SDBP_RemoveCStr(SWIGTYPE_p_void.getCPtr(client_), key, len);
  }

  public static int SDBP_ListKeys(SWIGTYPE_p_void client, String key, long count, long offset) {
    return scaliendb_clientJNI.SDBP_ListKeys(SWIGTYPE_p_void.getCPtr(client), key, count, offset);
  }

  public static int SDBP_ListKeysCStr(SWIGTYPE_p_void client, byte[] key, int len, long count, long offset) {
    return scaliendb_clientJNI.SDBP_ListKeysCStr(SWIGTYPE_p_void.getCPtr(client), key, len, count, offset);
  }

  public static int SDBP_ListKeyValues(SWIGTYPE_p_void client, String key, long count, long offset) {
    return scaliendb_clientJNI.SDBP_ListKeyValues(SWIGTYPE_p_void.getCPtr(client), key, count, offset);
  }

  public static int SDBP_ListKeyValuesCStr(SWIGTYPE_p_void client, byte[] key, int len, long count, long offset) {
    return scaliendb_clientJNI.SDBP_ListKeyValuesCStr(SWIGTYPE_p_void.getCPtr(client), key, len, count, offset);
  }

  public static int SDBP_Count(SWIGTYPE_p_void client, String key, long count, long offset) {
    return scaliendb_clientJNI.SDBP_Count(SWIGTYPE_p_void.getCPtr(client), key, count, offset);
  }

  public static int SDBP_CountCStr(SWIGTYPE_p_void client, byte[] key, int len, long count, long offset) {
    return scaliendb_clientJNI.SDBP_CountCStr(SWIGTYPE_p_void.getCPtr(client), key, len, count, offset);
  }

  public static int SDBP_Begin(SWIGTYPE_p_void client) {
    return scaliendb_clientJNI.SDBP_Begin(SWIGTYPE_p_void.getCPtr(client));
  }

  public static int SDBP_Submit(SWIGTYPE_p_void client) {
    return scaliendb_clientJNI.SDBP_Submit(SWIGTYPE_p_void.getCPtr(client));
  }

  public static int SDBP_Cancel(SWIGTYPE_p_void client) {
    return scaliendb_clientJNI.SDBP_Cancel(SWIGTYPE_p_void.getCPtr(client));
  }

  public static boolean SDBP_IsBatched(SWIGTYPE_p_void client) {
    return scaliendb_clientJNI.SDBP_IsBatched(SWIGTYPE_p_void.getCPtr(client));
  }

  public static void SDBP_SetTrace(boolean trace) {
    scaliendb_clientJNI.SDBP_SetTrace(trace);
  }

}
