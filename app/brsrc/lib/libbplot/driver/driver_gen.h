/**********************************************************************

Filename    :   BPlotDriverGen.h
Content     :   Generic driver.

Created     :   April 24, 2013
Authors     :   Boris Rayskiy

Copyright   :   (c) 2013

**********************************************************************/

#ifndef _B_PLOT_DRIVER_GEN_H_
#define _B_PLOT_DRIVER_GEN_H_


#include <BTypes.h>
#include <bplot_driver.h>
#include <BColor.h>
#include <iostream>
#include <sstream>


using namespace BoriSoft;
using namespace BoriSoft::graph;
using namespace BoriSoft::data;


struct DevParam
{
    UInt16 width;
    UInt16 height;
    UInt16 densityDpi;

    friend std::ostream& operator << (std::ostream& os, const DevParam& src)
    {
        return os << "["
                  << "width = " << src.width << ", "
                  << "height = " << src.height << ", "
                  << "densityDpi = " << src.densityDpi
                  << "]";
    }

}; // struct DevParam


class GenDev : public BDev
{

public:

    GenDev()
        : m_density(0)
    {}

    ~GenDev()
    {
        m_density = 0;
    }

    virtual Float GetResX(void)
    {
        return m_density;
    }

    virtual Float GetResY(void)
    {
        return m_density;
    }

    virtual SInt32 GetPhyXmin(void)   { return (SInt32)0;    }
    virtual SInt32 GetPhyXmax(void)   { return (SInt32)xRes; }
    virtual SInt32 GetPhyYmin(void)   { return (SInt32)0;    }
    virtual SInt32 GetPhyYmax(void)   { return (SInt32)yRes; }

    const Float& density(void) const { return m_density; }
    Float& density(void) { return m_density; }

private:

    friend std::ostream& operator << (std::ostream& os, const GenDev& src)
    {
        return os << "["
                  << "xRes = "    << src.xRes   << ", "
                  << "yRes = "    << src.yRes   << ", "
                  << "width = "   << src.width  << ", "
                  << "height = "  << src.height << ", "
                  << "density = " << src.m_density
                  << "]";
    }

private:

    Float m_density;

};


class BPlotDriverGen : public BPlotDriver
{
    GenDev*            genDev;
    BColor             color;
    std::ostringstream buf;

public:

    BPlotDriverGen() 
        : genDev(new GenDev)
        , color(BColor(0, 0, 0))
    {}

    void Init(const void* ptr)
    {
        DevParam* param = (DevParam *)ptr;

        genDev->width     = param->width;
        genDev->height    = param->height;
        genDev->density() = (Float)param->densityDpi / 25.4;
        genDev->xRes      = param->width;
        genDev->yRes      = param->height;
    }

    void* GetDev(void)           { return (void *)genDev; }
    void  SetPlotLog(void* pLog) {}
    
    SInt32 GetXRes(void)   { return genDev->GetPhyXmax();  }
    SInt32 GetYRes(void)   { return genDev->GetPhyXmax();  }
    Float  GetXScale(void) { return genDev->xScale;        }
    Float  GetYScale(void) { return genDev->yScale;        }

    void  SetColor(BColor col, SInt32 width) 
    {
        color = col;

        SInt32 outCol = (SInt32)((0xFF << 24) + (color.R() << 16) +
                        (color.G() << 8) + color.B());

        buf << "{\"tag\": \"pen\","
            << "\"color\": \"" << outCol << "\","
            << "\"width\": \"" << width << "\"},";
    }

    void Line(SInt32 X1, SInt32 Y1, SInt32 X2, SInt32 Y2)
    {
        buf << "{\"tag\": \"line\","
            << "\"x1\": \"" << X1                  << "\","
            << "\"y1\": \"" << (genDev->yRes - Y1) << "\","
            << "\"x2\": \"" << X2                  << "\","
            << "\"y2\": \"" << (genDev->yRes - Y2) << "\"},";
    }

    void Polyline(SInt32* x, SInt32* y, SInt32 n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            Line(x[i], y[i], x[i + 1], y[i + 1]);
        }
    }

    void FillPolygon(SInt32* x, SInt32* y, SInt32 n)
    {
        buf << "{\"tag\": \"fill\", \"points\": [";
       
        for (SInt32 i = 0; i < n; ++i)
        {
            buf << "{"
                << "\"x\": \"" << x[i]                  << "\","
                << "\"y\": \"" << (genDev->yRes - y[i]) << "\"}";
            if (i < (n - 1)) buf << ",";
        }
        
        buf << "]},";
    }

    void BeginOfPage(void)
    {
        BColor color(0, 0, 0);
        SetColor(color, 1);
    }

    void EndOfPage(void) {}
    void Tidy(void)      {}

    std::ostringstream& getBuf(void) { return buf; }

    ~BPlotDriverGen()
    {
        if (genDev)
        {
            delete genDev;
            genDev = 0;
        }
    }

private:

    friend std::ostream& operator << (std::ostream& os, const BPlotDriverGen& src)
    {
        return os << "["
                  << "genDev = " << *src.genDev
                  << "]";
    }

}; // class BPlotDriverGen


#endif // _B_PLOT_DRIVER_GEN_H_
