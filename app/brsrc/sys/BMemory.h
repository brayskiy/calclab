/**********************************************************************

Filename    :   BMemory.h
Content     :   

Created     :   June 5, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/

#ifndef _B_MEMORY_H_
#define _B_MEMORY_H_


#include <BTypes.h>
#include <BList.h>
#include <string.h>


namespace BoriSoft {
namespace sys {


class BSysAllocator
{

public:

    static void*    Alloc(UInt32 Size);
    static void*    Realloc(void* Ptr, UInt32 Size);
    static void     Free(void* Ptr);
};


struct BMemoryDebugInfo : public data::BListNode<BMemoryDebugInfo>
{
    UPInt   Address;
    UPInt   Size;
    UPInt   Line;
    char*   File;
};


class BMemDebug
{    
public:

    static void Init();
    static void AddEntry(void* Ptr, UPInt Size, UPInt Line, const char* File);
    static void RemEntry(void* Ptr);
    static void DetectMemLeaks(void);
    static void Clear(void);

};


class BAllocator
{
public:

    static void*    Alloc(UInt32 Size, UInt32 Line, const char* File);
    static void*    Realloc(void* Ptr, UInt32 Size, UInt32 Line, const char* File);
    static void     Free(void* Ptr);

};


#define BLINE __LINE__
#define BFILE __FILE__


#define BALLOC(Ptr, Type, ArraySize, Line, File) \
{\
    Ptr = (Type *)sys::BAllocator::Alloc(((ArraySize) * sizeof(Type)), Line, File);\
}
    

#define BREALLOC(Ptr, Type, ArraySize, Line, File) \
{\
    Ptr = (Type *)sys::BAllocator::Realloc((void *)Ptr, ((ArraySize) * sizeof(Type)), Line, File);\
}


#define BFREE(Ptr) \
{\
    if (Ptr)\
    {\
        sys::BAllocator::Free(Ptr);\
        Ptr = NULL;\
    }\
}


#define MATCALLOC(Ptr, Type, N, M, Line, File) {\
    Ptr = (Type **)sys::BAllocator::Alloc(N * sizeof(Type*), Line, File);\
    for (SInt32 i = 0; i < N; ++i)\
    {\
        Ptr[i] = (Type *)sys::BAllocator::Alloc(M * sizeof(Type), Line, File);\
    }\
}


#define MATFREE(Ptr, Type, N, M) \
{\
    for (SInt32 i = 0; i < N; ++i)\
    {\
        sys::BAllocator::Free(Ptr[i]);\
    }\
    sys::BAllocator::Free(Ptr);\
    Ptr = NULL;\
}



// New and delete.

/*
BINLINE void* operator new(size_t Size, UPInt Line, char* File)
{
    void* Ptr = ::operator new(Size);
    if (Ptr)
    {
        BMemDebug::AddEntry(Ptr, Size, Line, File);
    }
    return Ptr;
}


BINLINE void operator delete(void* Ptr, UByte)
{
    BMemDebug::RemEntry(Ptr);
    ::operator delete(Ptr);
}
*/


} // namespace sys
} //namespace BoriSoft


#endif // _B_MEMORY_H_
