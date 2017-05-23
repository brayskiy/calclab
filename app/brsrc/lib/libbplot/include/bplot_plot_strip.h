/**********************************************************************

Filename    :   BPlotStrip.h
Content     :   

Created     :   March 10, 2001
Authors     :   Boris Rayskiy

Copyright   :   (c) 2001-2009

**********************************************************************/


#include <bplot.h>


enum BPlotStripConst
{
    //PENSIL_INCREMENT = 4,
    POINTS_INCREMENT = 128,
};


class CStrip
{

public:

    Float xmin, xmax, ymin, ymax, xjump, xlen;
    Float wxmin, wxmax, wymin, wymax;
    char *xspec, *yspec, *labx, *laby, *labtop;
    SInt32 y_ascl, acc, colbox, collab;
    Float xlpos, ylpos;

};


class BPlotStrip : public BPlot
{

public:

    BPlotStrip(BPlotDriver* driver) : BPlot(driver) {}
    BPlotStrip(BPlotDriver* driver, SInt32 nx, SInt32 ny) : BPlot(driver, nx, ny) {}

    ~BPlotStrip() {}

    void DrawChart(UInt32 stripNumber, char*, char*, 
                   Float, Float, Float, Float, Float, Float, Float, 
                   SInt32, SInt32, SInt32, SInt32, 
                   SInt32*, SInt32*, char*[], char*, char*, char*);

    void AddPoint(SInt32, Float, Float);

private:

    void generateChart();
    void generateLegend(SInt32);

private:

    UInt32 StripNumber;

    CStrip  cstrip;
    CStrip* stripc;

    BDynamicArray<BDynamicArray<Float> > xom;
    BDynamicArray<BDynamicArray<Float> > yom;

    BDynamicArray<SInt32> npts;
    BDynamicArray<SInt32> colline;
    BDynamicArray<SInt32> styline;
    BDynamicArray<Char*>  legline;

};
