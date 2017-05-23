/**********************************************************************

Filename    :   BList.h
Content     :   

Created     :   June 15, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/

#ifndef _B_LIST_H_
#define _B_LIST_H_

#include <BTypes.h>


namespace BoriSoft {
namespace data {


template<class T> struct BListNode
{
    T* pPrev;
    T* pNext;
};


template<class T> class BList
{

public:

    BList()
    {
        Root.pNext = Root.pPrev = &Root;
    }

    void RemoveAll()
    {
        Root.pNext = Root.pPrev = &Root;
    }

    T* GetFirst() { return Root.pNext; }
    T* GetLast () { return Root.pPrev; }

    bool IsFirst(const T* p) const { return p == Root.pNext; }
    bool IsLast (const T* p) const { return p == Root.pPrev; }
    bool IsNull (const T* p) const { return p == (const T*)&Root; }

    BINLINE static const T* GetPrev(const T* p) { return p->pPrev; }
    BINLINE static const T* GetNext(const T* p) { return p->pNext; }
    BINLINE static       T* GetPrev(      T* p) { return p->pPrev; }
    BINLINE static       T* GetNext(      T* p) { return p->pNext; }


    void PushFront(T* p)
    {
        p->pNext          =  Root.pNext;
        p->pPrev          =  &Root;
        Root.pNext->pPrev =  p;
        Root.pNext        =  p;
    }


    void PushBack(T* p)
    {
        p->pPrev          =  Root.pPrev;
        p->pNext          =  &Root;
        Root.pPrev->pNext =  p;
        Root.pPrev        =  p;
    }


    void Remove(T* p)
    {
        p->pPrev->pNext = p->pNext;
        p->pNext->pPrev = p->pPrev;
    }


    void BringToFront(T* p)
    {
        Remove(p);
        PushFront(p);
    }


    void SendToBack(T* p)
    {
        Remove(p);
        PushBack(p);
    }

private:

    // Copying is prohibited.
    BList(const BList<T>& v);
    const BList<T>& operator = (const BList<T>& v);

    T Root;

}; // class BList


} // namespace data
} // namespace BoriSoft


#endif // _B_LIST_H_
