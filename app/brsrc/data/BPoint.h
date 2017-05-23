/**********************************************************************

Filename    :   BPoint.h
Content     :   

Created     :   April 10, 2002
Authors     :   Boris Rayskiy

Copyright   :   (c) 2002-2009

**********************************************************************/


#ifndef _B_POINT_H_
#define _B_POINT_H_


#include <BTypes.h>
#include <algorithm>
#include <iostream>

extern "C" {
#include <math.h>
};


namespace BoriSoft {
namespace data {


template<typename T> class BPoint
{
public:
	
    BPoint() {}

    ///BPoint(T& x0, T& y0) 
    //    : x(x0)
    //    , y(y0)
    //{}

    BPoint(T x0, T y0) 
        : x(x0)
        , y(y0)
    {}
    
    BPoint(T& a)
        : x(a)
        , y(a)
    {}
    
    BPoint(const BPoint& rhs)
    {
        *this = rhs;
    }

    BPoint& operator = (const BPoint& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        return *this;
    }

    BPoint& operator = (const T& a)
    {
        this->x = a;
        this->y = a;
        return *this;
    }

    BPoint operator +(const BPoint& p) { return BPoint(x + p.x, y + p.y); }
    const BPoint operator +(const BPoint& p) const { return BPoint(x + p.x, y + p.y); }
    BPoint operator +(const T& a) { return BPoint(x + a, y + a); }
    const BPoint operator +(const T& a) const { return BPoint(x + a, y + a); }
    BPoint operator -(const BPoint& p) { return BPoint(x - p.x, y - p.y); }
    const BPoint operator -(const BPoint& p) const { return BPoint(x - p.x, y - p.y); }
    BPoint operator -(const T& a) { return BPoint(x - a, y - a); }
    const BPoint operator -(const T& a) const { return BPoint(x - a, y - a); }
    BPoint operator *(const BPoint& p) { return BPoint(x * p.x, y * p.y); }
    const BPoint operator *(const BPoint& p) const { return BPoint(x * p.x, y * p.y); }
    BPoint operator *(const T& a) { return BPoint(x * a, y * a); }
    const BPoint operator *(const T& a) const { return BPoint(x * a, y * a); }
    BPoint operator -() { return BPoint(-x, -y); }
    const BPoint operator -() const { return BPoint(-x, -y); }
    BPoint& operator +=(const BPoint& p) { x += p.x; y += p.y; return *this; }
    const BPoint& operator +=(const BPoint& p) const { x += p.x; y += p.y; return *this; }
    BPoint& operator -=(const BPoint& p) { x -= p.x; y -= p.y; return *this; }
    const BPoint& operator -=(const BPoint& p) const { x -= p.x; y -= p.y; return *this; }
    BPoint& operator *=(const BPoint& p) { x *= p.x; y *= p.y; return *this; }
    const BPoint& operator *=(const BPoint& p) const { x *= p.x; y *= p.y; return *this; }
    
    bool operator ==(const BPoint& p) { return (x == p.x && y  == p.y); }
    bool operator !=(const BPoint& p) { return (x != p.x || y  != p.y); }

    bool operator >(const BPoint& p)
    {
        return (y > p.y) ? true : (y < p.y) ? false : (x > p.x) ? true : false;
    }

    bool operator >= (const BPoint& p) { return ((*this > p) || (*this == p)); }  
    bool operator <  (const BPoint& p) { return !(*this >= p);                 }
    bool operator <= (const BPoint& p) { return ((*this < p) || (*this == p)); }

    T compare(const BPoint& p)
    {
        if (y < p.y)
        {
            return -1;
        }
        else if(y > p.y)
        {
            return 1;
        }

        if(x < p.x)
        {
            return -1;
        } 
        else if(x > p.x)
        {
            return 1;
        }
        return 0;
    }

    // Distance between two points.
    T operator %(const BPoint& p)
    {
        return (T)((Double)((x - p.x) * (x - p.x)) +
                   (Double)((y - p.y) * (y - p.y)));
    }


    BPoint& polar(const BPoint& Center, const T& Radius, const T& Angle)
    {
        x = (T)((Double)Center.x + (Double)Radius * ::cos((Double)Angle));
        y = (T)((Double)Center.y + (Double)Radius * ::sin((Double)Angle));
    
        return *this;
    }


    BPoint& rotate(const BPoint& Center, const T Angle)
    {
        T xTmp = Center.x + (T)((x - Center.x) * ::cos((Double)Angle) - 
                                (y - Center.y) * ::sin((Double)Angle));
        T yTmp = Center.y + (T)((y - Center.y) * ::cos((Double)Angle) + 
                                (x - Center.x) * ::sin((Double)Angle));
        x = xTmp;
        y = yTmp;
        
        return *this;
    }


    // Rotate on 45 degree around zero point.
    BPoint& rotate45(const SInt32& sens)
    {
        T xTmp = x - sens * y;
        T yTmp = x * sens + y;
        x = xTmp / std::max(1, ::abs(xTmp));
        y = yTmp / std::max(1, ::abs(yTmp));

        // Same as the next call. But it does not work for integer types.
        //return this->rotate(BPoint<T>(0, 0), (T)(sens * PI / 4.f));
        
        return *this;
    }


    // Rotate on 135 (180 - 45) degree around zero point.
    BPoint& rotate135(const SInt32& sens)
    {
        x = -x;
        y = -y;

        return this->rotate45(sens);
    }


    BPoint&  mirrorX(void)   { x = x; y = -y; return *this; }
    BPoint&  mirrorY(void)   { x = -x; y = y; return *this; }
    T&       X(void)         { return x;                    }
    const T& X(void) const   { return x;                    }
    T&       Y(void)         { return y;                    }
    const T& Y(void) const   { return y;                    }
    void     X(const T& arg) { x = arg;                     }
    void     Y(const T& arg) { y = arg;                     }

private:

    friend std::ostream& operator << (std::ostream& os, const BPoint& src)
    {
        os << "[" << src.x << ", " << src.y << "]";
        return os;
    }

private:

    T x;
    T y;

}; // class BPoint


} // namespace data
} // namespace BoriSoft


#endif // _B_POINT_H_
