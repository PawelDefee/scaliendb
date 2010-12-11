#ifndef STORAGEPAGE_H
#define STORAGEPAGE_H

#include "System/Platform.h"
#include "System/Buffers/Buffer.h"

/*
===============================================================================================

 StoragePage

===============================================================================================
*/

class StoragePage
{
public:    
    void                SetOffset(uint64_t);
    uint32_t            GetOffset();
    
    virtual uint32_t    GetSize() = 0;

    virtual void        Write(Buffer& writeBuffer) = 0;

private:
    uint64_t    offset;
};

#endif
