/**********************************************************************

Filename    :   BArray.h
Content     :   Handling Dynamic arrays.

Created     :   June 15, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/


#ifndef _B_ARRAY_H_
#define _B_ARRAY_H_


#include <BTypes.h>
#include <string.h>


namespace BoriSoft {
namespace data {


template<class T> class BArray
{

public:

    BArray(UInt32 size) 
        : m_size(size)
        , m_array(new T[size])
    {
        clear();
    }


    ~BArray()
    {
        delete [] m_array;
    }


    void clear()
    {
        memset(m_array, 0, m_size * sizeof(T));
    }
    
    T& operator [](UInt32 i) { return m_array[i]; }
    const T& operator [](UInt32 i) const { return m_array[i]; }
    const T* getArray(void) const { return m_array; }
    T* getArray(void) { return m_array; }
    const UInt32 size() const { return m_size; }

private:

    UInt32 m_size;
    T*     m_array;

}; // class BArray


/**********************************************************************

Filename    :   BDynamicArray.h
Content     :   Handling Dynamic arrays.

Created     :   June 16, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/

template <class T> class BDynamicArray
{

public:

    BDynamicArray(UPInt gran = 1024)
        : m_gran(gran)
        , m_max_size(m_gran)
        , m_size(0)
        , m_array(new T[m_gran]) 
        , m_tmp_array(0)
    {}


    BDynamicArray(const BDynamicArray<T>& src)
    {
        m_gran     = src.m_gran;
        m_max_size = src.m_max_size;
        m_size     = src.m_size;
        m_array    = new T[m_max_size];
        memcpy(m_array, src.m_array, sizeof(T) * m_max_size);
    }


    ~BDynamicArray()
    {
        delete [] m_array;
    }


    void clear(void)
    {
        delete [] m_array;
        m_array    = new T[m_gran];
        m_max_size = m_gran;
        m_size     = 0;
    }


    BDynamicArray& operator =(const BDynamicArray& src)
    {
        delete [] m_array;
        m_gran     = src.m_gran;
        m_max_size = src.m_max_size;
        m_size     = src.m_size;
        m_array    = new T[m_max_size];
		memcpy(m_array, src.m_array, sizeof(T) * m_size);
        return *this;
    }


    const UPInt size(void) const { return m_size; }
    const UPInt max_size(void) const { return m_max_size; }
    const T* getArray(void) const { return m_array; }
    T* getArray(void) { return m_array; }
    const T& operator [](UPInt i) const { return m_array[i]; }


    // Used as a get element and as a dynamically set element function.
    T& operator [](UPInt i) 
    {
        if (i >= m_max_size)
        {
            resize(i);
        }
	
        if (i == m_size)
        {
            ++m_size;
        }
        else if (i > m_size)
        {
            m_size = i;
        }
        
        return m_array[i];
    }


    void resize(UPInt size)
    {
        size = (size & (~(m_gran - 1))) + m_gran;
        m_tmp_array = new T[size];
        m_max_size  = size;
        memset(m_tmp_array, 0, m_max_size * sizeof(T));
        memcpy(m_tmp_array, m_array, m_size * sizeof(T));
        delete [] m_array;
        m_array     = m_tmp_array;
        m_tmp_array = NULL;
    }


    void cut(UPInt size)
    {
        m_tmp_array = new T[size];
        memcpy(m_tmp_array, m_array, size * sizeof(T));
        delete [] m_array;
        m_array 	= m_tmp_array;
        m_tmp_array = NULL;
        m_size      = size;
        m_max_size  = size;
    }


    void erase(const UPInt ind)
    {
        if (ind < (m_size - 1))
        {
             memcpy(&m_array[ind], &m_array[ind + 1], sizeof(T) * (m_size - ind - 1));
             --m_size;

             if ((m_size + m_gran) <= m_max_size)
             {
                 //Cut(ArraySize - Granularity);
                 resize(m_max_size - m_gran - 1);
             }
        }
    }


    void insert(const UPInt ind, const T& element)
    {
        if (ind < (m_max_size - 1)) // Element should be inserted.
        {
            if (m_size >= m_max_size) resize(m_size);  // Resize if array is full.
            memmove(&m_array[ind + 1], &m_array[ind], sizeof(T) * (m_size - ind));
            memcpy(&m_array[ind], &element, sizeof(T));
            ++m_size;
        }
        else // But index is out of ArraySize
        {
            resize(ind + 1);
            memcpy(&m_array[ind], &element, sizeof(T));
            m_size = ind + 1;
        }
    }	
	

    void push_back(const T& element)
    {
        if (m_size >= m_max_size)
        {
            resize(m_size);
        }
        memcpy(&m_array[m_size++], &element, sizeof(T));
    }

private:

    UPInt m_gran;
    UPInt m_max_size;
    UPInt m_size;
    T*    m_array;
    T*    m_tmp_array;

}; // class BDynamicArray


/**********************************************************************

Filename    :   BMatrix.h
Content     :   Handling Dynamic arrays.

Created     :   June 16, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/

template<class T> class BMatrix
{

public:

    BMatrix(UInt32 sizeX, UInt32 sizeY) 
        : SizeX(sizeX)
        , SizeY(sizeY)
    {
        Matrix = new T *[SizeX];
        for (UInt32 i = 0; i < SizeX; ++i)
        {
            Matrix[i] = new T[SizeY];
        }

        Size = SizeX * SizeY;

        Clear();
    }


    BMatrix(const T* src, UInt32 sizeX, UInt32 sizeY)
        : SizeX(sizeX)
        , SizeY(sizeY)
    {
        Matrix = new T *[SizeX];
        for (UInt32 i = 0; i < SizeX; ++i)
        {
            Matrix[i] = new T[SizeY];
        }

        Size = SizeX * SizeY;

        for (UInt32 i = 0; i < sizeX; ++i)
        {
            for (UInt32 j = 0; j < sizeY; ++j)
            {
                Matrix[i][j] = src[i + j * sizeX];
            }
        }
    }


    ~BMatrix()
    {
        for (UInt32 i = 0; i < SizeX; ++i)
        {
             delete [] Matrix[i];
        }
        delete [] Matrix;
    }

    void Clear()
    {
        for (UInt32 i = 0; i < SizeX; ++i)
        {
            memset(Matrix[i], 0, SizeY * sizeof(T));
        }
    }

    T**     GetMatrix(void)                 { return Matrix;        }
    UInt32  GetSizeX() const                { return SizeX;         }
    UInt32  GetSizeY() const                { return SizeY;         }
    UInt32  GetSize() const                 { return Size;          }
    T&      GetElement(UInt32 i, UInt32 j)  { return Matrix[i][j];  }

private:

    UInt32  SizeX;
    UInt32  SizeY;
    UInt32  Size;
    T**     Matrix;
    T       Current;

}; // class BMatrix


} // namespace data
} // namespace BoriSoft


#endif // _B_ARRAY_H_
