/**********************************************************************

Filename    :   BPlotDriverPPM.h
Content     :   PPM driver.

Created     :   July 30, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/



#ifndef _B_PLOT_DRIVER_PPM_H_
#define _B_PLOT_DRIVER_PPM_H_


#include <bplot_driver.h>
#include <BColor.h>
#include <BMath.h>
#include <BMemory.h>
#include <BArray.h>
#include <stdio.h>
#include <string.h>


using namespace BoriSoft;
using namespace BoriSoft::graph;
using namespace BoriSoft::data;


class BPlotLog;


class BPPMDev : public BDev
{

public:

    virtual Float   GetResX(void)     { return (Float)(xRes / 150.f / width * height);  }
    virtual Float   GetResY(void)     { return (Float)(yRes / 150.f);                   }

    virtual SInt32 GetPhyXmin(void)   { return (SInt32)0;                               }
    virtual SInt32 GetPhyXmax(void)   { return (SInt32)xRes;                            }
    virtual SInt32 GetPhyYmin(void)   { return (SInt32)0;                               }
    virtual SInt32 GetPhyYmax(void)   { return (SInt32)yRes;                            }

}; 


class BPlotDriverPPM : public BPlotDriver
{
    BPPMDev*    PPMDev;
    char*       FileName;
    UInt32      FileNumber;
    UByte*      DumpBuf;
    UPInt       BufSize;
    FILE*       FileDesc;
    BColor      Color;

public:

    BPlotDriverPPM() { PPMDev = NULL; }

    void        Init(const void* ptr);
    void*       GetDev(void);
    void        SetPlotLog(void* pLog) {}
    void        SetColor(BColor color, SInt32 width);
    void        Line(SInt32 x1, SInt32 y1, SInt32 x2, SInt32 y2);
    void        Polyline(SInt32* x, SInt32* y, SInt32 n);
    void        FillPolygon(SInt32* x, SInt32* y, SInt32 n);
    void        BeginOfPage(void);
    void        EndOfPage(void);
    void        Tidy(void);

    ~BPlotDriverPPM() { if (PPMDev) delete PPMDev; }

private:

    void        setPixel(SInt32 x, SInt32 y, BColor color);
    BColor      getPixel(SInt32 x, SInt32 y);

};

#endif // _B_PLOT_DRIVER_PPM_H_