/**********************************************************************

Filename    :   BVector.h
Content     :   BVector class is handling operations with vectors.

Created     :   October 18, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/

#ifndef _B_VECTOR_H_
#define _B_VECTOR_H_


#include <BPoint.h>


namespace BoriSoft {
namespace data {


template<typename T> class BVector
{

public:

    BVector()
    {
        p0 = BPoint<T>();
        p1 = BPoint<T>();
    }


    BVector(const BPoint<T>& p)
    {
        p0 = BPoint<T>();
        p1 = p;
    }


    BVector(const BPoint<T>& vp0, const BPoint<T>& vp1)
    {
        p0 = vp0;
        p1 = vp1;
    }


    BVector(const BVector<T>& v)
    {
        p0 = v.p0;
        p1 = v.p1;
    }


    BPoint<T> P0(void)
    {
        return p0;
    }


    BPoint<T> P1(void)
    {
        return p1;
    }


    BVector<T> operator +(const BVector<T>& v) { return BVector(p0, v.p1 - v.p0 + p1);      }
    BVector<T> operator -()                    { return BVector(p0, p0 * 2 - p1);           }
    BVector<T> operator -(const BVector<T>& v) { return BVector(p0, (-v).p1 - (-v).p0 + p1);}
    BVector<T> operator *(const T& a)          { return BVector<T>(p0 * a, p1 * a);         }


    T operator*(BVector<T>& v)
    {
        return (p1.X() - p0.X()) * (v.p1.X() - v.p0.X()) +
               (p1.Y() - p0.Y()) * (v.p1.Y() - v.p0.Y());
    }


    BVector<T>& operator  =(const BVector<T>& v) { p0 = v.p0; p1 = v.p1; return *this; }
    BVector<T>& operator  =(const BPoint<T>& p)  { p0 = 0; p1 = p;       return *this; }
    BVector<T>& operator +=(const BVector<T>& v) { p1 += v.p1 - v.p0;    return *this; }
    BVector<T>& operator +=(const BPoint<T>& p)  { p1 += p;              return *this; }
    BVector<T>& operator -=(const BVector<T>& v) { p1 += v.p0 - v.p1;    return *this; }
    BVector<T>& operator -=(const BPoint<T>& p)  { p1 -= p;              return *this; }

    bool operator==(const BVector<T>& v)         { return (p0 == v.p0) && (p1 = v.p1); }
    
    T Dot(void)                                  { return p0 % p1;                     }
    

    T length(void)
    {
        return (T)math::sqrt((Double)Dot());
    }


    T distance(const BPoint<T>& p)
    {
        BVector<Double> v(p1 - p0);
        BVector<Double> w(p - p0);

        Double c1 = w * v;
        if (c1 <= 0)
        {
            return BVector(p, p0).Length();
        }
        Double c2 = v * v;
        if (c2 <= c1)
        {
            return BVector(p, p1).Length();
        }
        Double b = c1 / c2;
        BPoint<T> Pb = p0 + v.p1 * b;
        return BVector(p, Pb).length();
    }

private:

    BPoint<T> p0;
    BPoint<T> p1;

}; // class BVector


} // namespace data
} // namespace BoriSoft


#endif // _B_VECTOR_H_
