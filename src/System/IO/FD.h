#ifndef FD_H
#define FD_H

#include "System/Platform.h"

// File descriptor abstraction

// On Windows the file handle is a pointer, on unices it is a
// growing index in an array in the process, thus it can be used
// as an array index in IOProcessor. We emulate this behavior on
// Windows.

// TODO: rename sock to handle

#ifdef _WIN32
struct FD
{
	bool		operator==(const FD& other);
	bool		operator!=(const FD& other);

    int         index;
    intptr_t    handle;
};

inline bool FD::operator==(const FD& other)
{
    if (index == other.index && handle == other.handle)
        return true;
    return false;
}

inline bool FD::operator!=(const FD& other)
{
    return !operator==(other);
}

extern const FD INVALID_FD;

#else
typedef int FD;
#define INVALID_FD -1
#endif

#endif
