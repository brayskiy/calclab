/**********************************************************************

Filename    :   BStd.h
Content     :   

Created     :   August 14, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/

#ifndef _B_STD_H_
#define _B_STD_H_


#include <BTypes.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#ifdef WIN32
#include <share.h>
#endif

namespace BoriSoft {
namespace bstd {


BINLINE char* strcpy(char* dest, char* src)
{
#ifdef WIN32
    ::strcpy_s(dest, strlen(src) + 1, src);
    return dest;
#else
    return ::strcpy(dest, src);
#endif
}


BINLINE char* strncpy(char* dest, int destsize, char* src, int srcsize)
{
#ifdef WIN32
    ::strncpy_s(dest, destsize, src, srcsize);
    return dest;
#else
    return ::strncpy(dest, src, destsize);
#endif
}


BINLINE UInt32 fopen(FILE** file, const char* filename, const char* filemode)
{
UInt32 rc = 0;
#ifdef WIN32
    rc = (UInt32)::fopen_s(file, filename, filemode);
#else
    *file = ::fopen(filename, filemode);
    rc = (*file == 0) ? 1 : 0;
#endif

    return rc;
}


BINLINE void tmpfile(FILE** file)
{
#ifdef WIN32
    *file = _fsopen("tmp", "wb+", _SH_DENYNO);
    //*file = ::tmpfile();
    //brs::std::fopen(file, "tmp", "w");
#else
    *file = ::tmpfile();
#endif
    //::fopen_s(file, "tmp", "w+");
    //*file = ::fopen("tmp", "w+");
}

       
BINLINE UInt32 sprintf(char* ptr, UPInt size, const char* format, va_list list)
{
#ifdef WIN32
    if (size == 0)
    {
        size = (UPInt)(~(0));
    }
    return (UInt32)::sprintf_s(ptr, size, format, list);
#else
    return (UInt32)::sprintf(ptr, format, list);
#endif    
}


BINLINE UInt32 vsnprintf(char* ptr, UPInt size, UPInt maxSize, 
                         const char* format, va_list list)
{
#ifdef WIN32
    return (UInt32)::vsnprintf_s(ptr, size, maxSize, format, list);
#else
    return (UInt32)::vsnprintf(ptr, size, format, list);
#endif
}


BINLINE UInt32 vsnprintf(char* ptr, UPInt size, UPInt maxSize, 
                         const char* format, ...)
{
    va_list list;        
    va_start(list, format);
#ifdef WIN32
    return (UInt32)::vsnprintf_s(ptr, size, maxSize, format, list);
#else
    return (UInt32)::vsnprintf(ptr, size, format, list);
#endif
    va_end(list);
}


BINLINE UInt32 Bsprintf(char* ptr, UPInt size, const char* format, ...)
{
    va_list list;
    va_start(list, format);
    UInt32 ret = bstd::sprintf(ptr, size, format, list);
    va_end(list);
    return ret;
}


} // namespace bstd
} // namespace BoriSoft


#endif // _B_STD_H_
