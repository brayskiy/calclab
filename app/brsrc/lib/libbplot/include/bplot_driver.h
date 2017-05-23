/**********************************************************************

Filename    :   BPlotDriver.h
Content     :   BPlot driver base class.

Created     :   July 30, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/


#ifndef _B_PLOT_DRIVER_H_
#define _B_PLOT_DRIVER_H_


#include <BTypes.h>
#include <BColor.h>


using namespace BoriSoft;


class BDev
{

public:

    BDev()
        : xRes(0)
        , yRes(0)
        , xScale(0)
        , yScale(0)
        , width(0)
        , height(0)
    {}

    ~BDev()
    {
        xRes   = 0;
        yRes   = 0;
        xScale = 0;
        yScale = 0;
        width  = 0;
        height = 0;
    }

    virtual Float GetResX(void) { return (Float)0; }
    virtual Float GetResY(void) { return (Float)0; }

    virtual SInt32 GetPhyXmin(void) { return 0; }
    virtual SInt32 GetPhyXmax(void) { return 0; }
    virtual SInt32 GetPhyYmin(void) { return 0; }
    virtual SInt32 GetPhyYmax(void) { return 0; }

public:

    Float   xRes;
    Float   yRes;
    Float   xScale;
    Float   yScale;

    SInt32  width;
    SInt32  height;
}; 


class BPlotDriver
{

public:

    BPlotDriver()   {}

    virtual void    Init(const void* ptr)                            = 0;
    virtual void*   GetDev(void)                                     = 0;
    virtual void    SetPlotLog(void* pLog)                           = 0;
    virtual void    SetColor(graph::BColor color, int width)         = 0;
    virtual void    Line(SInt32 x1, SInt32 y1, SInt32 x2, SInt32 y2) = 0;
    virtual void    Polyline(SInt32* x, SInt32* y, SInt32 npts)      = 0;
    virtual void    FillPolygon(SInt32* x, SInt32* y, SInt32 npts)   = 0;
    virtual void    BeginOfPage(void)                                = 0;
    virtual void    EndOfPage(void)                                  = 0;
    virtual void    Tidy(void)                                       = 0;

    virtual SInt32  GetXRes(void)   { return 0; }
    virtual SInt32  GetYRes(void)   { return 0; }
    virtual Float   GetXScale(void) { return 0; }
    virtual Float   GetYScale(void) { return 0; }
    virtual void    Display()       {}

    virtual ~BPlotDriver() {}

};

#endif // _B_PLOT_DRIVER_H_
