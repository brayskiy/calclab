/**********************************************************************

Filename    :   BMemory.cpp
Content     :   

Created     :   March 25, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/


#include <BMemory.h>
#include <BPrintf.h>
#ifdef __DARWIN__
#include <stdlib.h>
#else
#include <malloc.h>
#endif


namespace BoriSoft {
namespace sys {


void* BSysAllocator::Alloc(UInt32 Size)
{
    void* Ptr = malloc(Size);
    if (Ptr)
    {
        memset(Ptr, 0, Size);
    }
    return Ptr;
}


void* BSysAllocator::Realloc(void* Ptr, UInt32 Size)
{
    Ptr = realloc(Ptr, Size);
    return Ptr;
}


void BSysAllocator::Free(void* Ptr)
{
    free((void *)Ptr);
}


data::BList<BMemoryDebugInfo> MemoryDebugList;
UInt32 NumDebugEntry;


void BMemDebug::Init()
{
    NumDebugEntry = 0;
}


void  BMemDebug::AddEntry(void* Ptr, UPInt Size, UPInt Line, const char* File)
{
    BMemoryDebugInfo* MemoryDebugEntry = 
        (BMemoryDebugInfo *)BSysAllocator::Alloc(sizeof(BMemoryDebugInfo));

    MemoryDebugEntry->Address    = (UPInt)Ptr;
    MemoryDebugEntry->Size       = Size;
    MemoryDebugEntry->Line       = Line;
    MemoryDebugEntry->File       = const_cast<char*>(File);

    MemoryDebugList.PushBack(MemoryDebugEntry);
    ++NumDebugEntry;
}


void BMemDebug::RemEntry(void* Ptr)
{
    if (!Ptr) return;

    BMemoryDebugInfo* MemoryDebugEntry = MemoryDebugList.GetFirst();
    while (!MemoryDebugList.IsNull(MemoryDebugEntry))
    {
        if ((UPInt)Ptr == MemoryDebugEntry->Address)
        {
            MemoryDebugList.Remove(MemoryDebugEntry);
            BSysAllocator::Free((void *)MemoryDebugEntry);
            --NumDebugEntry;
            return;
        }
        MemoryDebugEntry = MemoryDebugList.GetNext(MemoryDebugEntry);
    }
}


void BMemDebug::DetectMemLeaks(void)
{
    bstd::BPrintf leaks;
    leaks.Init("MemoryLeaks.txt");

    BMemoryDebugInfo* MemoryDebugEntry = MemoryDebugList.GetFirst();
    while (!MemoryDebugList.IsNull(MemoryDebugEntry))
    {
        leaks.Printf("Ptr: %d, File %s, Line %d\n",
                     MemoryDebugEntry->Address,
                     MemoryDebugEntry->File,
                     MemoryDebugEntry->Line);
        MemoryDebugEntry = MemoryDebugList.GetNext(MemoryDebugEntry);
    }
    leaks.Printf("Number of entries: %d\n", NumDebugEntry);
    leaks.Close();
}


void BMemDebug::Clear(void)
{
    BMemoryDebugInfo* MemoryDebugEntry = MemoryDebugList.GetFirst();
    while (!MemoryDebugList.IsNull(MemoryDebugEntry))
    {
        MemoryDebugList.Remove(MemoryDebugEntry);
        delete MemoryDebugEntry;
        --NumDebugEntry;
        MemoryDebugEntry = MemoryDebugList.GetFirst();
    }
}



void* BAllocator::Alloc(UInt32 Size, UInt32 Line, const char* File)
{
    void* Ptr = BSysAllocator::Alloc(Size);
    if (Ptr)
    {
        BMemDebug::AddEntry(Ptr, Size, Line, File);
    }
    return Ptr;
}


void* BAllocator::Realloc(void* Ptr, UInt32 Size, UInt32 Line, const char* File)
{
    if (Ptr)
    {
        BMemDebug::RemEntry(Ptr);
    }
    Ptr = BSysAllocator::Realloc(Ptr, Size);
    BMemDebug::AddEntry(Ptr, Size, Line, File);
    return Ptr;
}


void BAllocator::Free(void* Ptr)
{
    BMemDebug::RemEntry(Ptr);
    BSysAllocator::Free(Ptr);
}


} // namespace sys
} // namespace BoriSoft
