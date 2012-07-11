#include "Memory.h"

// route C++ style memory management
void* operator new (size_t sz)
{
    return malloc(sz);
}

void* operator new[] (size_t sz)
{
    return malloc(sz);
}

void operator delete (void *p)
{
    free(p);
}

void operator delete[] (void *p)
{
    free(p);
}
