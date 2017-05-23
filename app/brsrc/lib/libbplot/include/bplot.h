/**********************************************************************

Filename    :   BPlot.h
Content     :   BPlot header file.

Created     :   March 16, 2001
Authors     :   Boris Rayskiy

Copyright   :   (c) 2001-2009

**********************************************************************/


#ifndef _B_PLOT_H_
#define _B_PLOT_H_

#include <bplot_stream.h>
#include <BPoint.h>
#include <BColor.h>
#include <bplot_plot_log.h>
#include <BMemory.h>
#include <bplot_driver.h>
#include <BArray.h>
#include <vector>
#include <bplot_exception.h>


using namespace BoriSoft;


class BPlot
{

public:

    BPlot(BPlotDriver* driver);
    BPlot(BPlotDriver* driver, SInt32 nx, SInt32 ny);
	
    ~BPlot();

    void BeginOfPage(void);
    void EndOfPage(void);
    void Display(void);

    /* Color */
    void SetColor(BColor color);
    /* Set pen width. */
    void SetWidth(SInt32);
	
    /* Font loader */
    void FontLoad(SInt32);
    /* Sets the global font flag to 'ifont'. */
    void SetFont(SInt32) throw(util::BPlotException);
    void fontsize(Float, Float);

    /* Advance to subpage "page", or to the next one if "page" = 0. */
    void adv(SInt32) throw(util::BPlotException);
    /* View Port Setup */	
    /* Simple interface for defining viewport and window. */
    void env(Float, Float, Float, Float, SInt32, SInt32) throw(util::BPlotException);
    /* This draws a box around the current viewport. */
    void box(char*, Float, SInt32, char*, Float, SInt32);
    /* Defines a "standard" viewport with seven character heights for */
    /* the left margin and four character heights everywhere else. */
    void vsta(void);
    /* Creates a viewport with the specified normalized subpage coordinates. */
    void vpor(Float, Float, Float, Float) throw(util::BPlotException);
    /* Set up world coordinates of the viewport boundaries (2d plots). */
    void SetWorldCoord(Float, Float, Float, Float);
    /* Sets the edges of the viewport to the specified absolute coordinates */
    void svpa(Float, Float, Float, Float) throw(util::BPlotException);
    /* Sets the edges of the viewport with the given aspect ratio, leaving room for labels. */
    void vasp(Float);
    /* Simple routine for labeling graphs. */
    void lab(const char*, const char*, const char*);
    
    void Point(SInt32 n, Float* x, Float* y, SInt32 code);
    void Point(Float x, Float y, SInt32 code);
    void Line(Float, Float, Float, Float);
    void Line(BPoint<Float>, BPoint<Float>);
    void PolyLine(SInt32, Float*, Float*);
    void PolyLine(BPoint<Float>*, SInt32);
    void PolyLine(const std::vector<Float>& x, const std::vector<Float>& y);
    void PolyLine(const BArray<Float>& x, const BArray<Float>& y);
    void PolyLine(const BDynamicArray<Float>& x, const BDynamicArray<Float>& y);
    void ArrowTwo(BPoint<Float>, BPoint<Float>);
    void DimensionX(BPoint<Float>, BPoint<Float>, Float);
    void DimensionY(BPoint<Float>, BPoint<Float>, Float);
    void DimensionA(BPoint<Float>, BPoint<Float>, BPoint<Float>);
    void DimensionA(BPoint<Float>, Float, Float, Float);
    void DimensionA(BPoint<Float>*);
    
    /* Circles and Arcs */
    void Circle(BPoint<Float>, Float);
    void Arc(BPoint<Float> p1, BPoint<Float> p2, BPoint<Float> p3);
    void Arc(BPoint<Float>, Float, Float, Float);
    void Segment(BPoint<Float>, Float, Float, Float);
    
    /* Styles */
    void SetStyle(SInt32);
    void plpsty(SInt32);
    void plstyl(SInt32, SInt32*, SInt32*);
    
    void FillPolygon(SInt32 n, Float*, Float*);
    void FillPolygon(SInt32 n, BPoint<Float>* p);
    
    BPoint<Double> PhyToWorld(BPoint<Double> p); 
    
    /* Plots array y against x for n points using Hershey symbol "code" */
    void WriteSymbol(SInt32, Float*, Float*, SInt32) throw(util::BPlotException);
    
    /* Prints out "text" at world coordinate (x,y). */
    void TextOutWord(Float, Float, Float, Float, Float, const char*);
    /* Prints out "text" at specified position relative to viewport */
    void TextOutVPort(const char*, Float, Float, Float, const char*);
    
    /* Draws a histogram of n values of a variable in array data[0..n-1] */
    void DrawHistogram(SInt32, Float*, Float, Float, SInt32, SInt32) throw(util::BPlotException);
    
    /* Set up a window for three-dimensional plotting. */
    void plw3d(Float, Float, Float, Float, Float, Float, Float, Float, Float, Float, Float);
    void plbox3(const char*, const char*, Float, SInt32, const char*, const char*, Float, SInt32, const char*, const char*, Float, SInt32);
    void plot3d(Float*, Float*, Float**, SInt32, SInt32, SInt32, SInt32, SInt32);
    void plotsh3d(Float*, Float*, Float**, SInt32, SInt32, SInt32, SInt32);
    void plmesh(Float*, Float*, Float**, SInt32, SInt32, SInt32);
    void plside3(Float*, Float*, Float**, SInt32, SInt32, SInt32);
    /* Sets the position of the light source */
    void SetLightSource(Float, Float, Float);
    /* Draws a line in 3 space.  */
    void Line3D(SInt32, Float*, Float*, Float*);
    /* Draws a polygon in 3 space.  */
    void PolyLine3D(SInt32, Float*, Float*, Float*, SInt32*);
    /* Draws a series of points in 3 space. */
    void Point3D(SInt32, Float*, Float*, Float*, SInt32) throw(util::BPlotException);
    
    /* Draws a Contour plot from data in f(nx,ny). */
    void Contour(Float**, Float**, Float**, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, Float*, SInt32, SInt32);
    void Contour(Float**, Float*, Float*, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, Float*, SInt32, SInt32);
    void Contour(Float**, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, Float*, SInt32, SInt32);
    /* Sets offset and spacing of contour labels */
    void setcontlabelparam(Float, Float, Float, SInt32);
    
    /* Shade */
    void plshade(Float**, Float**, Float**, SInt32, SInt32, SInt32 (*)(Float, Float), Float, Float, Float, Float, Float, Float, SInt32, Float, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32);
    void plshade(Float**, Float*, Float*, SInt32, SInt32, SInt32 (*)(Float, Float), Float, Float, Float, Float, Float, Float, SInt32, Float, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32);
    void plshade(Float**, SInt32, SInt32, SInt32, SInt32, SInt32 (*)(Float, Float), Float, Float, Float, Float, Float, Float, SInt32, Float, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32);
    void plshades(Float**, Float**, Float**, SInt32, SInt32, SInt32 (*)(Float, Float), Float, Float, Float, Float, Float*, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32);
    void plshades(Float**, Float*, Float*, SInt32, SInt32, SInt32 (*)(Float, Float), Float, Float, Float, Float, Float*, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32);
    void plshades(Float**, SInt32, SInt32, SInt32, SInt32, SInt32 (*)(Float, Float), Float, Float, Float, Float, Float*, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32);
    
    /* Map */
    void plmap(void(*)(SInt32, Float*, Float*), char*, Float, Float, Float, Float);
    void plmeridians(void (*)(SInt32, Float*, Float*), Float, Float, Float, Float, Float, Float);
    
    /* Plot Version */ 
    const char* version(void);
    /* Replot */
    void Replot(void);
    
protected:
    
    CStream*  m_bStream;
    BPlotLog* plotLog;

}; //class BPlot


#endif // _B_PLOT_H_
