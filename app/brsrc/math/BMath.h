/**********************************************************************

Filename    :   BMath.h
Content     :   Handles Math functions.

Created     :   September 24, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/


#ifndef _B_MATH_H_
#define _B_MATH_H_


#include <BTypes.h>
#include <BPoint.h>
#include <math.h>


#define PI_NUM          3.1415926535897932384626433832795
#define PI2             6.28318530717958647692528676655901
#define PISCO           0.0506605918211688857219397316048638    // 1 / (2 * PI * PI)
#ifndef M_PI_2
#define M_PI_2          1.57079632679489661923132169163975      // PI / 2
#endif
#define PIO4            0.78539816339744830962
#define SQ2OPI          0.79788456080286535588
#define TWOOPI          6.36619772367581343075535E-1
#define THPIO4          2.35619449019234492885
#define LOG4            1.3862943611198906188E0                 // log(4)
#define MACHEP          1.11022302462515654042E-16              // 2**-53 

#define EPSILON         1e-12


namespace BoriSoft {
namespace math {


template<typename T> BINLINE T sign(T a)      { return ((a < (T)0) ? (T)-1 : (T)1); }
template<typename T> BINLINE T sign(T a, T b) { return ((a < b) ? (T)-1 : (T)1);    }
template<typename T> BINLINE T abs(T a)       { return ((a < 0) ? -a : a);          }
template<typename T> BINLINE T bmin(T a, T b) { return ((a < b) ? a : b);           }
template<typename T> BINLINE T bmax(T a, T b) { return ((a > b) ? a : b);           }


template<typename T> BINLINE SInt32 round(T a)
{
    return (SInt32)((a < (T)0) ? (a - (T)0.5) : (a + (T)0.5));
}


template<typename T> BINLINE bool betw(T x, T a, T b)
{
    return (((x <= a) && (x >= b)) || ((x >= a) && (x <= b)));
}


template<typename T> BINLINE bool inside(T x, T y, T xmin, T xmax, T ymin, T ymax)
{
    return (betw(x, xmin, xmax) && betw(y, ymin, ymax));
}


template<typename T> BINLINE bool inside(data::BPoint<T> p, T xmin, T xmax, T ymin, T ymax)
{
    return (betw(p.X(), xmin, xmax) && betw(p.Y(), ymin, ymax));
}


template<typename T> BINLINE T square(T x)    { return (x * x);                          }
template<typename T> BINLINE T cube(T x)      { return (x * x * x);                      }
template<typename T> BINLINE T sqrt(T x)      { return (T)::sqrt((Double)x);             }
template<typename T> BINLINE T ssqr(T a, T b) { return (T)sqrt((Double)(a * a + b * b)); }
template<typename T> BINLINE T sin(T x)       { return (T)::sin((Double)x);              }
template<typename T> BINLINE T cos(T x)       { return (T)::cos((Double)x);              }


BINLINE void matminmax(Float** a, SInt32 n, SInt32 m, Float& Min, Float& Max)
{
    Min = Max = a[0][0];
    for (SInt32 i = 0; i < n; i++)
    {
        for(SInt32 j = 0; j < m; j++)
        {
            Max = math::bmax(Max, a[i][j]);
            Min = math::bmin(Min, a[i][j]);
        }
    }
}


template<typename T> BINLINE T det3(T a11, T a12, T a13,
                                    T a21, T a22, T a23,
                                    T a31, T a32, T a33)
{
    return a11 * (a22 * a33 - a23 * a32) - 
           a12 * (a21 * a33 - a31 * a23) + 
           a13 * (a21 * a32 - a31 * a22);
}


// Polynomial calculation.
BINLINE Double polevl(Double x, Double* coef, int N )
{
    Double ans;
    int i;
    Double* p;
    p = coef;
    ans = *p++;
    i = N;

    do ans = ans * x + *p++; while(--i);
    return(ans);
}


BINLINE Double p1evl(Double x, Double* coef, int N)
{
    Double ans;
    Double *p;
    int i;

    p = coef;
    ans = x + *p++;
    i = N - 1;

    do ans = ans * x  + *p++; while(--i);
    return(ans);
}


// Elliptical integrals.
// Complete elliptical integral of the first kind.
BINLINE Double elint1(Double x)
{
    static Double P1[] = 
    {  
        1.37982864606273237150E-4,
        2.28025724005875567385E-3,
        7.97404013220415179367E-3,
        9.85821379021226008714E-3,
        6.87489687449949877925E-3,
        6.18901033637687613229E-3,
        8.79078273952743772254E-3,
        1.49380448916805252718E-2,
        3.08851465246711995998E-2,
        9.65735902811690126535E-2,
        1.38629436111989062502E0
   };

   static Double Q1[] =
   {
        2.94078955048598507511E-5,
        9.14184723865917226571E-4,
        5.94058303753167793257E-3,
        1.54850516649762399335E-2,
        2.39089602715924892727E-2,
        3.01204715227604046988E-2,
        3.73774314173823228969E-2,
        4.88280347570998239232E-2,
        7.03124996963957469739E-2,
        1.24999999999870820058E-1,
        4.99999999999999999821E-1
    };

    x = (Double)1. - math::square(x);
    if (x > MACHEP)
    { 
        return(polevl(x, P1, (int)10) - log(x) * polevl(x, Q1, (int)10));
    }        
    else
    {
        return(LOG4 - (Double)0.5 * log(x));
    }
}


// Complete elliptical integral of the second kind.
BINLINE Double elint2(Double x)
{
    static Double P2[] =
    {    
        1.53552577301013293365E-4,
        2.50888492163602060990E-3,
        8.68786816565889628429E-3,
        1.07350949056076193403E-2,
        7.77395492516787092951E-3,
        7.58395289413514708519E-3,
        1.15688436810574127319E-2,
        2.18317996015557253103E-2,
        5.68051945617860553470E-2,
        4.43147180560990850618E-1,
        1.00000000000000000299E0
    };

    static Double Q2[] =
    {
        3.27954898576485872656E-5,
        1.00962792679356715133E-3,
        6.50609489976927491433E-3,
        1.68862163993311317300E-2,
        2.61769742454493659583E-2,
        3.34833904888224918614E-2,
        4.27180926518931511717E-2,
        5.85936634471101055642E-2,
        9.37499997197644278445E-2,
        2.49999999999888314361E-1
    };

    x = (Double)1. - math::square(x);	
    return(polevl(x, P2, (int)10) - log(x) * (x * polevl(x, Q2, (int)9)));
}


// Generalized complete elliptical integral.
BINLINE Double comeli(Double a, Double b, Double c)
{ 
    Double an[5], as[5];

    an[0] = (Double)1.;
    an[1] = sqrt((Double)1. - c * c);
    an[2] = (Double)1.;
    an[3] = (b + (Double)1.) / ((Double)1. - a);
    an[4] = ((Double)1. - a) / an[1];

    while (abs(an[2] - an[3]) > (Double)EPSILON)
    {
        for (int n = 0; n < (int)5; ++n) as[n] = an[n];
        an[0] = (Double)0.5 * (as[0] + as[1]);
        an[1] = sqrt(as[0] * as[1]);
        an[2] = (Double).5 * (as[2] + as[3]);
        an[3] = (as[2] + as[3] * as[4]) / (as[4] + (Double)1.);
        an[4] = an[1] * (as[4] + 1.) * (as[4] + 1.) / ((Double)4. * an[0] * as[4]);
    }
    return (an[2] * M_PI_2 / an[0]);
}


} // namespace math
} // namespace BoriSoft


#endif // _B_MATH_H_
