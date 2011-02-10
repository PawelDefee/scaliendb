#include "StorageLogSegment.h"
#include "System/FileSystem.h"
#include "System/IO/IOProcessor.h"
#include "System/Stopwatch.h"
#include "System/Compress/Compressor.h"

StorageLogSegment::StorageLogSegment()
{
    prev = next = this;
    logSegmentID = 0;
    fd = INVALID_FD;
    logCommandID = 1;
    prevContextID = 0;
    prevShardID = 0;
    writeShardID = true;
    asyncCommit = false;
}

#define Log_DebugLong(sw, ...)  \
    if (sw.Elapsed() > 1000)    \
    do {                        \
        Log_Debug(__VA_ARGS__); \
        sw.Reset();             \
    } while (0)

bool StorageLogSegment::Open(Buffer& filename_, uint64_t logSegmentID_)
{
    unsigned    length;
    Stopwatch   sw;
    
    sw.Start();
    
    filename.Write(filename_);
    filename.NullTerminate();
    fd = FS_Open(filename.GetBuffer(), FS_CREATE | FS_WRITEONLY | FS_APPEND);
    if (fd == INVALID_FD)
        return false;

    sw.Stop();
    
    Log_DebugLong(sw, "log segment Open() took %U msec", (uint64_t) sw.Elapsed());

    logSegmentID = logSegmentID_;
    offset = 0;

    sw.Start();
    writeBuffer.AppendLittle64(logSegmentID);
    length = writeBuffer.GetLength();
    
    if (FS_FileWrite(fd, writeBuffer.GetBuffer(), length) != length)
    {
        FS_FileClose(fd);
        fd = INVALID_FD;
        return false;
    }
    offset += length;

    sw.Stop();

    Log_DebugLong(sw, "log segment Open() took %U msec, length = %u", (uint64_t) sw.Elapsed(), length);

    sw.Start();
    FS_Sync(fd);
    sw.Stop();

    Log_DebugLong(sw, "log segment Open() took %U msec", (uint64_t) sw.Elapsed());
    
    NewRound();
    
    Log_Debug("Opening log segment %U", logSegmentID);
        
    return true;
}

void StorageLogSegment::Close()
{
    FS_FileClose(fd);
    fd = INVALID_FD;
    writeBuffer.Reset();
}

void StorageLogSegment::DeleteFile()
{
    FS_Delete(filename.GetBuffer());
}

uint64_t StorageLogSegment::GetLogSegmentID()
{
    return logSegmentID;
}

uint32_t StorageLogSegment::GetLogCommandID()
{
    return logCommandID;
}

void StorageLogSegment::SetOnCommit(Callable* onCommit_)
{
    onCommit = onCommit_;
    asyncCommit = true;
}

int32_t StorageLogSegment::AppendSet(uint16_t contextID, uint64_t shardID,
 ReadBuffer& key, ReadBuffer& value)
{
    assert(fd != INVALID_FD);

    prevLength = writeBuffer.GetLength();

    writeBuffer.Appendf("%c", STORAGE_LOGSEGMENT_COMMAND_SET);
    if (!writeShardID && contextID == prevContextID && shardID == prevShardID)
    {
        writeBuffer.Appendf("%b", true); // use previous shardID
    }
    else
    {
        writeBuffer.Appendf("%b", false);
        writeBuffer.AppendLittle16(contextID);
        writeBuffer.AppendLittle64(shardID);
    }
    writeBuffer.AppendLittle16(key.GetLength());
    writeBuffer.Append(key);
    writeBuffer.AppendLittle32(value.GetLength());
    writeBuffer.Append(value);

    writeShardID = false;
    prevContextID = contextID;
    prevShardID = shardID;
    return logCommandID++;
}

int32_t StorageLogSegment::AppendDelete(uint16_t contextID, uint64_t shardID, ReadBuffer& key)
{
    assert(fd != INVALID_FD);

    prevLength = writeBuffer.GetLength();

    writeBuffer.Appendf("%c", STORAGE_LOGSEGMENT_COMMAND_DELETE);

    if (!writeShardID && contextID == prevContextID && shardID == prevShardID)
    {
        writeBuffer.Appendf("%b", true); // use previous shardID
    }
    else
    {
        writeBuffer.Appendf("%b", false);
        writeBuffer.AppendLittle16(contextID);
        writeBuffer.AppendLittle64(shardID);
    }
    writeBuffer.AppendLittle16(key.GetLength());
    writeBuffer.Append(key);

    writeShardID = false;
    prevContextID = contextID;
    prevShardID = shardID;
    return logCommandID++;
}

void StorageLogSegment::Undo()
{
    writeBuffer.SetLength(prevLength);
    logCommandID--;
    writeShardID = true;
}

void StorageLogSegment::Commit()
{
    uint32_t    length;
    uint32_t    checksum;
    ReadBuffer  dataPart;
    Buffer      compressed;
    Compressor  compressor;
    
    commitStatus = true;

    assert(fd != INVALID_FD);

    length = writeBuffer.GetLength();

    assert(length >= STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE);
    
    if (length == STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE)
        return; // empty round

    dataPart.SetBuffer(writeBuffer.GetBuffer() + STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE);
    dataPart.SetLength(length - STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE);
//    checksum = dataPart.GetChecksum();
    checksum = 0;
    
    assert(compressor.Compress(dataPart, compressed));

//    Log_Debug("uncompressed = %s, compressed = %s", HUMAN_BYTES(dataPart.GetLength()),
//     HUMAN_BYTES(compressed.GetLength()));

    length = STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE + compressed.GetLength();
    
    writeBuffer.SetLength(0);
    writeBuffer.AppendLittle32(length);
    writeBuffer.AppendLittle32(dataPart.GetLength());
    writeBuffer.AppendLittle32(checksum);
    writeBuffer.SetLength(STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE);
    writeBuffer.Append(compressed);
    
//    Log_Debug("Commit");

    sw.Start();    
/*
    if (FS_FileWrite(fd, writeBuffer.GetBuffer(), length) != length)
    {
        FS_FileClose(fd);
        fd = INVALID_FD;
        commitStatus = false;
        return;
    }
*/
  // TEST CODE
    #define WRITE_SIZE 64*1024
    unsigned ws;
    for (unsigned ofs = 0; ofs < length; ofs += ws)
    {
        ws = MIN(WRITE_SIZE, length - ofs);
        if (FS_FileWrite(fd, writeBuffer.GetBuffer() + ofs, ws) != ws)
        {
            FS_FileClose(fd);
            fd = INVALID_FD;
            commitStatus = false;
            return;
        }
        FS_Sync(fd);
    }
    // TEST CODE END


    offset += length;

    sw.Stop();
    Log_DebugLong(sw, "log segment Commit took %U msec, length: %u", (uint64_t) sw.Elapsed(), length);

    FS_Sync(fd);
    
    Log_DebugLong(sw, "log segment Sync took %U msec", (uint64_t) sw.Elapsed());

    NewRound();
    
    if (asyncCommit)
        IOProcessor::Complete(onCommit);
}

bool StorageLogSegment::GetCommitStatus()
{
    return commitStatus;
}

bool StorageLogSegment::HasUncommitted()
{
    return (writeBuffer.GetLength() > STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE);
}

uint64_t StorageLogSegment::GetOffset()
{
    return offset;
}

void StorageLogSegment::NewRound()
{
    // reserve:
    // 4 bytes for size
    // 4 bytes for uncompressedLength
    // 4 bytes for CRC
    writeBuffer.Allocate(STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE);
    writeBuffer.Zero();
    writeBuffer.SetLength(STORAGE_LOGSEGMENT_BLOCK_HEAD_SIZE);    

    prevLength = writeBuffer.GetLength();
}
