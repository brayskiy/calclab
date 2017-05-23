/**********************************************************************

Filename    :   BPlotLog.h
Content     :   

Created     :   March 25, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/


#ifndef _B_PLOT_LOG_H_
#define _B_PLOT_LOG_H_


#include <BTypes.h>
#include <bplot_driver.h>
#include <BStd.h>
#include <BArray.h>


using namespace BoriSoft;


class BPlotDriver;


class BPlotLog
{
    enum BPlotLogCode
    {
        INITIALIZE,
        EOP,
        BOP,
        DISPLAY,
        LINE,
        POLYLINE,
        FILLPOLYGON,
        SETCOLOR,
        UNKNOWN,
    };

public:

	//BPlotLog() : lock(new BLock()) {}
	//~BPlotLog() { delete lock; }

    // Write section.

public:

    void Init(void* ptr);
    void SetColor(graph::BColor color, SInt32 width);
    void Line(SInt32 x1, SInt32 y1, SInt32 x2, SInt32 y2);
    // Draw a polyline in the current color.
    void Polyline(SInt32* x, SInt32* y, SInt32 n);
    // Fills polygon described in points x[] and y[].
    void FillPolygon(SInt32* x, SInt32* y, SInt32 n);
    void Display(void);
    void BeginOfPage(void);
    void EndOfPage(void);
    
    // Read section.

private:

    void SetColorR(void);
    // Draw a line in the current color from (x1,y1) to (x2,y2).
    void LineR(void);
    // Draw a polyline in the current color.
    void PolylineR(void);
    // Handle change in CStream state (color, pen width, fill attribute, etc).
    void FillPolygonR(void);
    void DisplayR(void);
    void BeginOfPageR(void);
    void EndOfPageR(void);

public:

    // Rebuilds plot from plot buffer, usually in response to a window resize 
    // or exposure event.
    void replot(void);

	// MEMBERS

	bool         WriteEnabled;
    FILE*        LogFile;
    BPlotDriver* driver;
    BPlotLogCode c;


};

#endif // _B_PLOT_LOG_H_