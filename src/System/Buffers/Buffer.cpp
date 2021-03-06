#include "Buffer.h"
#include "System/Common.h"
#include <stdarg.h>
#include <stdlib.h>
#include <new>

Buffer::Buffer()
{
    Init();
}

Buffer::~Buffer()
{
    if (buffer != array && !preallocated)
        free(buffer);
}

void Buffer::SetPreallocated(char* buffer_, unsigned size_)
{
    preallocated = true;
    buffer = buffer_;
    size = size_;
}

int Buffer::Cmp(const Buffer& a, const Buffer& b)
{
    int ret;
    unsigned alen, blen;

    alen = a.length;
    blen = b.length;
    ret = memcmp(a.buffer, b.buffer, MIN(alen, blen));
    
    if (ret != 0)
        return ret;
        
    if (alen < blen)
        return -1;
    else if (blen < alen)
        return 1;
    else
        return 0;
}

int Buffer::Cmp(const char* buffer_, unsigned length_)
{
    int ret;
    unsigned alen, blen;

    alen = length;
    blen = length_;
    ret = memcmp(buffer, buffer_, MIN(alen, blen));
    
    if (ret != 0)
        return ret;
        
    if (alen < blen)
        return -1;
    else if (blen < alen)
        return 1;
    else
        return 0;
}

int Buffer::Cmp(const char* str)
{
    int ret;
    unsigned alen, blen;

    alen = length;
    blen = strlen(str);
    ret = memcmp(buffer, str, MIN(alen, blen));
    
    if (ret != 0)
        return ret;
        
    if (alen < blen)
        return -1;
    else if (blen < alen)
        return 1;
    else
        return 0;
}

void Buffer::Lengthen(unsigned k)
{
    length += k;
}

void Buffer::Shorten(unsigned k)
{
    length -= k;
}

void Buffer::Allocate(unsigned size_, bool keepold)
{
    char*       newbuffer;
        
    if (size_ <= size)
        return;

    size_ = NextPowerOfTwo(size_);

    if (buffer == array || preallocated)
        newbuffer = (char*) malloc(size_);
    else
        newbuffer = (char*) realloc(buffer, size_);

    if (newbuffer == NULL)
    {
        throw std::bad_alloc();
        // in case of exceptions are disabled
        STOP_FAIL(1, "Out of memory error");
    }

    if (keepold && length > 0)
    {
        if (buffer == array || preallocated)
            memcpy(newbuffer, buffer, length);
    }
    
    buffer = newbuffer;
    size = size_;
    preallocated = false;
}

int Buffer::Readf(const char* format, ...) const
{
    int         read;
    va_list     ap;
    
    va_start(ap, format);
    read = VReadf(buffer, length, format, ap);
    va_end(ap);
    
    return read;
}

unsigned Buffer::Writef(const char* fmt, ...)
{
    unsigned required;
    va_list ap;

    while (true)
    {
        va_start(ap, fmt);
        required = VWritef(buffer, size, fmt, ap);
        va_end(ap);
        
        if (required <= size)
        {
            length = required;
            break;
        }
        
        Allocate(required, false);
    }
    
    return length;
}

unsigned Buffer::Appendf(const char* fmt, ...)
{
    unsigned required;
    va_list ap;
    
    while (true)
    {
        va_start(ap, fmt);
        required = VWritef(GetPosition(), GetRemaining(), fmt, ap);
        va_end(ap);
        
        // snwritef returns number of bytes required
        if (required <= GetRemaining())
            break;
        
        Allocate(length + required, true);
    }
    
    length += required;
    return required;
}

void Buffer::Write(const char* buffer_, unsigned length_)
{
    if (length_ > size)
        Allocate(length_);
    memmove(buffer, buffer_, length_);
    length = length_;
}

void Buffer::Write(const char* str) 
{
    Write(str, strlen(str));
}

void Buffer::Write(const Buffer& other)
{
    Write(const_cast<Buffer&>(other).GetBuffer(), const_cast<Buffer&>(other).GetLength());
}

void Buffer::Write(const ReadBuffer& other)
{
    Write(other.GetBuffer(), other.GetLength());
}

void Buffer::Write(char c, unsigned num)
{
    Clear();
    Append(c, num);
}

void Buffer::Append(char c)
{
    Append(&c, 1);
}

void Buffer::Append(const char* buffer_, unsigned length_)
{
    if (length_ > GetRemaining())
        Allocate(length + length_);
    memcpy(GetPosition(), buffer_, length_);
    Lengthen(length_);
}

void Buffer::Append(const char* str)
{
    Append(str, strlen(str));
}

void Buffer::Append(const Buffer& other)
{
    Append(other.GetBuffer(), other.GetLength());
}

void Buffer::Append(ReadBuffer other)
{
    Append(other.GetBuffer(), other.GetLength());
}

void Buffer::Append(char c, unsigned num)
{
    unsigned i;
    
    for (i = 0; i < num; i++)
        Append(c);
}

void Buffer::AppendLittle16(uint16_t x)
{
    x = ToLittle16(x);
    Append((const char*) &x, sizeof(uint16_t));
}

void Buffer::AppendLittle32(uint32_t x)
{
    x = ToLittle32(x);
    Append((const char*) &x, sizeof(uint32_t));
}

void Buffer::AppendLittle64(uint64_t x)
{
    x = ToLittle64(x);
    Append((const char*) &x, sizeof(uint64_t));
}

char Buffer::GetCharAt(unsigned i)
{
    if (i > length - 1)
        ASSERT_FAIL();
    
    return *(buffer + i);
}

void Buffer::SetCharAt(unsigned i, char c)
{
    buffer[i] = c;
}

bool Buffer::IsAsciiPrintable()
{
    return ReadBuffer(*this).IsAsciiPrintable();
}

void Buffer::ToHexadecimal()
{
    unsigned        i;
    unsigned char   x;
    Buffer          printable;
    const char      digits[] = "0123456789ABCDEF";
    
    printable.Allocate(length * 3);
    for (i = 0; i < length; i++)
    {
        x = (unsigned char) buffer[i];
        printable.Append(digits[x / 16]);
        printable.Append(digits[x % 16]);
        if (i != length - 1)
            printable.Append(' ');
    }
        
    Write(printable);
}

void Buffer::NullTerminate()
{
    Append("", 1);
}

void Buffer::Zero()
{
    memset(buffer, 0, size);
}

void Buffer::ZeroRest()
{
    memset(buffer + length, 0, size - length);
}

void Buffer::SetLength(unsigned length_)
{
    length = length_;
    if (length > size)
        ASSERT_FAIL();
}

void Buffer::Init()
{
    buffer = array;
    size = SIZE(array);
    length = 0;
    preallocated = false;
    prev = next = this;
}

unsigned Buffer::GetSize() const
{
    return size;
}

char* Buffer::GetBuffer() const
{
    return buffer;
}

unsigned Buffer::GetLength() const
{
    return length;
}

unsigned Buffer::GetRemaining() const
{
    return size - length;
}

char* Buffer::GetPosition() const
{
    return buffer + length;
}

uint32_t Buffer::GetChecksum() const
{
    return ChecksumBuffer(buffer, length);
}

ReadBuffer Buffer::GetReadBuffer() const
{
    return ReadBuffer(*this);
}

void Buffer::Clear()
{
    length = 0;
}

void Buffer::Reset()
{
    if (buffer != array && !preallocated)
        free(buffer);
    
    Init();
}

Buffer::Buffer(const Buffer& other)
{
    Init();
    *this = other;  // call operator=()
}

Buffer& Buffer::operator=(const Buffer& other)
{
    if (other.size != size)
      Allocate(other.size, false);

    memcpy(buffer, other.buffer, other.size);
    length = other.length;
    prev = next = this;

    return *this;
}

bool Buffer::BeginsWith(const char* s)
{
    unsigned len;
    
    len = strlen(s);
    
    if (length < len)
        return false;

    if (strncmp(s, buffer, len) == 0)
        return true;
    else
        return false;
}

bool Buffer::BeginsWith(Buffer& other)
{
    if (length < other.length)
        return false;

    if (MEMCMP(buffer, other.length, other.buffer, other.length))
        return true;
    else
        return false;
}

