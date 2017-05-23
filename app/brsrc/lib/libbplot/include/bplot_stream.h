/**********************************************************************

Filename    :   BPlotStream.h
Content     :   

Created     :   March 10, 2001
Authors     :   Boris Rayskiy

Copyright   :   (c) 2001-2009

**********************************************************************/


/*--------------------------------------------------------------------------*\
* Define the CStream data structure.
*
* This contains a copy of every variable that is stream dependent, which
* tends to be those which are settable by the user and persist for longer
* than one plot.
*
*
***************************************************************************
*
* Misc control variables
*
* level	SInt32	Initialization level
* Get the (current) run level. 
* Valid settings are:
*   0	uninitialized 
*   1	initialized
*   2	viewport defined
*   3	world coords defined 
* program	char*	Program name
* verbose	SInt32	Be more verbose than usual
* debug	SInt32	Generate debugging output
* initialized	SInt32	Set if the stream has been initialized
*
***************************************************************************
*
* icol  	SInt32	Color map 0 entry, current color (0 <= icol0 <= ncol0)
* curcolor	RGB[]	Current color
*
* Variables governing pen width 
*
* width	Current pen width
*
* Variables used to pass information between the core and the driver 
*
* It would be nice to use the "dev_" prefix uniformly but changing
* all that old code would be quite a lot of work..
*
* device	SInt32	Graphics device id number
* color	SInt32	Set if color is available
* plbuf_read	SInt32	Set during a plot buffer redraw
* plbuf_write	SInt32	Set if driver needs to use the plot buffer
* dev_fill0	SInt32	Set if driver can do solid area fills
* dev_fill1	SInt32	Set if driver can do pattern area fills
* dev_dash     SInt32   Set if driver can do dashed lines
* dev_flush	SInt32	Set if driver wants to handle flushes itself
* termin	SInt32	Set for interactive devices
* family	SInt32	Set if familying is enabled
* member	SInt32	Number of current family member file open
* fflen	SInt32	Minimum field length to use in member file number
* DevName	char*	Device name
* OutFile	FILE	Output file pointer
* BaseName	char*	Output base name (i.e. family)
* FileName	char*	Output file name
* bytecnt	SInt32	Byte count for output stream
* page		SInt32	Page count for output stream
* linepos	SInt32	Line count for output stream
*
* These are used by the escape function (for area fill, etc).
*
* dev_npts	SInt32	Number of points we are plotting
* dev_x	short*	Pointer to array of x values 
* dev_y	short*	Pointer to array of x values 
*
***************************************************************************
*
* Driver interface (DI)
*
* diorot	Float	Rotation angle (in units of pi/2)
* page_status	SInt32	Flag to indicate current action
*
***************************************************************************
*
* fillPolygon pattern state information. 
* patt < 0: Hardware fill, if available (not implemented yet)
* patt == 0: Hardware fill, if available, solid
* patt > 0: Software fill
*
* patt		fillPolygon pattern number
* inclin	Array of inclinations in tenths of degree for fill lines
* delta	Array of spacings in micrometers between fill lines
* nps		Number of distinct line styles for fills
*
***************************************************************************
*
* Variables used in line drawing
*
* currx	Physical x-coordinate of current point
* curry	Physical y-coordinate of current point
* mark		Array of mark lengths in micrometers for broken lines
* space	Array of space lengths in micrometers for broken lines
* nms		Number of elements for current broken line style
* timecnt	Timer for broken lines
* alarm	Alarm indicating change of broken line status
* pendn	Flag indicating if pen is up or down
* curel	Current element within broken line
*
***************************************************************************
*
* Variables governing character strings
*
* esc		Text string escape character
*
***************************************************************************
*
* Scale factors for characters, symbols, and tick marks.
*
* scale	Scaling factor for chr, sym, maj, min.
* chr...	Character default height and current (scaled) height
* sym...	Symbol    default height and current (scaled) height
* maj...	Major tick default height and current (scaled) height
* min...	Minor tick default height and current (scaled) height
*
***************************************************************************
*
* Variables governing numeric axis label appearance
*
* setpre	Non-zero to set precision using "prec"
* precis	User-specified precision
* xdigmax..	Allowed #digits in axes labels
* xdigits..	Actual field widths (returned)
*
***************************************************************************
*
* Variables governing physical coordinate system
*
* vpp..	Viewport boundaries in physical coordinates
* spp..	Subpage  boundaries in physical coordinates
* clp..	Clip     boundaries in physical coordinates
* phy...	Physical device limits in physical coordinates
* um.		Number of micrometers in a pixel
* pmm		Number of pixels to a millimeter
*
***************************************************************************
*
* State variables for 3d plots
*
* base3.	World coordinate size of base for 3-d plot
* basec.	Position of centre of base for 3-d plot
* dom...	Minimum and maximum values for domain
* zzscl	Vertical (z) scale for 3-d plot
* ran..	Minimum and maximum z values for 3-d plot
* c..		Coordinate transformation from 3-d to 2-d
*
* Variables governing subpages and viewports.
*
* nsub...	Number of subpages on physical device
* cursub	Current subpage
* spd...	Subpage  boundaries in normalized device coordinates
* vpd...	Viewport boundaries in normalized device coordinates
* vpw...	Viewport boundaries in world coordinates
*
***************************************************************************
*
* Transformation variables
*
* wp....	Transformation variables for world  to physical conversion
* wm....	Transformation variables for world coordinates to mm
*
****************************************************************************
*
* Font related variables
*
* cfont           Current font number, replaces global 'font' in plsym.c
*                 This can be latter extended for font shape, series, family and size
*
\*--------------------------------------------------------------------------*/

#ifndef _B_PLOT_STREAM_H_
#define _B_PLOT_STREAM_H_


#include <BColor.h>
#include <BArray.h>
#include <BPoint.h>
#include <BPrintf.h>
#include <BStd.h>
#include <BMath.h>
#include <bplot_driver.h>
#include <bplot_plot_symbol.h>
#include <BMemory.h>
#include <BDebug.h>


#ifdef WIN32
#pragma warning(disable : 4996)
#endif


using namespace BoriSoft;
using namespace BoriSoft::graph;
using namespace BoriSoft::bstd;
using namespace BoriSoft::data;
using namespace BoriSoft::math;


class CStream
{

public:

    BPlotDriver* driver;

    SInt32 level;
    /* Error info */
    SInt32 error;
    BColor icol;
    BColor zbcol;
    SInt32 zbflg;
    Float zbtck;
    /* Variables governing pen width */
    SInt32 width;
    /* Fonts */
    SInt32 cfont;
    /* Char height */
    Float chrht;
    /* fillPolygon pattern info */
    SInt32 patt;

    /* Variables governing subpages and viewports. */
    SInt32 nsubx, nsuby, cursub;
    Float vpwxmi, vpwxma, vpwymi, vpwyma;
    Float vpdxmi, vpdxma, vpdymi, vpdyma;
    Float spdxmi, spdxma, spdymi, spdyma;

    /* Variables governing physical coordinate system */
    SInt32 vppxmi, vppxma, vppymi, vppyma;
    SInt32 clpxmi, clpxma, clpymi, clpyma;
    SInt32 phyxmi, phyxma, phyxlen, phyymi, phyyma, phyylen;

    /* Variables governing numeric axis label appearance */
    SInt32 xdigmax, ydigmax, zdigmax;
    SInt32 xdigits, ydigits, zdigits;

    /* Transformation variables */
    Float wpxscl, wpxoff, wpyscl, wpyoff;
    Float wmxscl, wmxoff, wmyscl, wmyoff;

    /* State variables for 3d plots */
    Float base3x, base3y, basecx, basecy;
    Float domxmi, domxma, domymi, domyma;
    Float zzscl, ranmi, ranma;
    Float cxx, cxy, cyx, cyy, cyz;

private:

    BPlotSymbol*    pSymbol;
    BPrintf         warnInfo;

    BColor          curcolor;
    SInt32          curwidth;

    SInt32          dev_npts;
    short*          dev_x;
    short*          dev_y;

    /* fillPolygon pattern info */
    SInt32          inclin[2];
    SInt32          delta[2];
    SInt32          nps;

    /* Variables used in line drawing */
    SInt32 currx, curry;
    SInt32 mark[10], space[10], nms;
    SInt32 timecnt, alarm, pendn, curel;

    /* Scale factors for characters, symbols, and tick marks. */
    Float scale;
    Float chrdef;
    Float symdef, symht;
    Float majdef, majht;
    Float mindef, minht;

    /* Variables governing numeric axis label appearance */
    SInt32 setpre, precis;

    /* Variables governing physical coordinate system */
    SInt32 sppxmi, sppxma, sppymi, sppyma;
    SInt32 umx, umy;
    Float xpmm, ypmm;

public:

    CStream();
    ~CStream();

    void Init(void);

    void SetDev(const char*);
    void SetSub(SInt32, SInt32);

    void SubPageInit(void);
    void plend(void);

    /* Set up the subpage boundaries according to the current subpage selected. */
    void SetSubPageBound(void);

    /* Set a given color from color map 0 by 8 bit RGB value */
    void SetColor(BColor);
    void SetColor(Float);
    /* Set pen width. */
    void SetWidth(SInt32);
    /* Style */
    void plstyl(SInt32, SInt32*, SInt32*);

    /* Box */
    void plaxes(Float, Float, const char*, Float, SInt32, const char*, Float, SInt32);
    void grid_box(const char*, Float, SInt32, const char*, Float, SInt32);
    void label_box(const char*, Float, const char*, Float);

    void plform(Float, Float, SInt32, char*, SInt32, SInt32);
    void plxybx(char*, char*, Float, Float, Float, Float, Float, Float, Float, SInt32, SInt32, SInt32*);
    void plxytx(Float, Float, Float, Float, Float, Float, Float, char*);
    void plzbx(char*, char*, SInt32, Float, Float, Float, Float, Float, Float, Float, Float, SInt32, SInt32*);
    void plztx(const char*, Float, Float, Float, Float, Float, Float, Float, Float, const char*);

    /* Determines precision of box labels */
    void pldprec(Float, Float, Float, SInt32, SInt32*, SInt32*, SInt32, Float*);

    /* All the drivers call this to set physical pixels/mm. */
    void setpxl(Float, Float);
    /* Sets up physical limits of plotting device. */
    void setphy(SInt32, SInt32, SInt32, SInt32);

    // Transformations returning physical coordinates.
    // Device coordinates to physical coordinates (x).
    SInt32   dcpcx(Float x)  { return (SInt32)(math::round(phyxmi + phyxlen * x));     }
    // Device coordinates to physical coordinates (y)
    SInt32   dcpcy(Float y)  { return (SInt32)(math::round(phyymi + phyylen * y));     }
    // Millimeters from bottom left-hand corner to physical coords (x).
    SInt32   mmpcx(Float x)  { return (SInt32)(math::round(phyxmi + xpmm * x));        }
    // Millimeters from bottom left-hand corner to physical coords (y).
    SInt32   mmpcy(Float y)  { return (SInt32)(math::round(phyymi + ypmm * y));        }
    
    // World coordinate to physical coordinate (x).
    SInt32   wcpcx(Float x)  { return (SInt32)(math::round(wpxoff + wpxscl * x));      }
    // World coordinate to physical coordinate (y).
    SInt32   wcpcy(Float y)  { return (SInt32)(math::round(wpyoff + wpyscl * y));      }

    // Physical coordinate (x) to world coordinate.
    Double pcwcx(Double x)
    {
        return (x / (Double)driver->GetXScale() - 
                (Double)wpxoff) / 
                (Double)wpxscl;
    }
    // Physical coordinate (y) to world coordinate.
    Double pcwcy(Double y)
    {
        return (((Double)driver->GetYRes() - y / 
                  (Double)driver->GetYScale()) - 
                  (Double)wpyoff) / (Double)wpyscl;
    }

    // Transformations returning device coordinates.
    // Physical coordinates to device coordinates (x)
    Float   pcdcx(SInt32 x)  { return (Float)((x - phyxmi) / (Float) phyxlen);  }
    // Physical coords to device coords (y).
    Float   pcdcy(SInt32 y)  { return (Float)((y - phyymi) / (double) phyylen); }
    
    // Millimeters from bottom left corner to device coords (x).
    Float   mmdcx(Float x)  { return ((Float)(x * xpmm / math::abs(phyxma - phyxmi))); }
    // Millimeters from bottom left corner to device coords (y).
    Float   mmdcy(Float y)  { return ((Float)(y * ypmm / math::abs(phyyma - phyymi))); }

    // Subpage coordinate to device coordinate (x).
    Float   scdcx(Float x)  { return ((Float)(spdxmi + (spdxma - spdxmi) * x)); }
    // Subpage coordinate to device coordinate (y).
    Float   scdcy(Float y)  { return ((Float)(spdymi + (spdyma - spdymi) * y)); }

    // Transformations returning millimeters.
    // Device coordinates to millimeters from bottom left-hand corner (x).
    Float   dcmmx(Float x)  { return ((Float)(x * math::abs(phyxma - phyxmi) / xpmm)); }
    // Device coordinates to millimeters from bottom left-hand corner (y).
    Float   dcmmy(Float y)  { return ((Float)(y * math::abs(phyyma - phyymi) / ypmm)); }
    
    // World coordinate into millimeters (x).
    Float   wcmmx(Float x)  { return ((Float)(wmxoff + wmxscl * x));                        }
    // World coordinate into millimeters (y).
    Float   wcmmy(Float y)  { return ((Float)(wmyoff + wmyscl * y));                        }

    // Transformations returning subpage coordinates.
    // Device coordinate to subpage coordinate (x).
    Float   dcscx(Float x)  { return ((Float)((x - spdxmi) / (spdxma - spdxmi)));           }
    // Device coordinate to subpage coordinate (y).
    Float   dcscy(Float y)  { return ((Float)((y - spdymi) / (spdyma - spdymi)));           }

    // 3-d plot transformations.
    // 3-d coordinate to 2-d projection (x).
    Float   w3wcx(Float x, Float y, Float z)
    { 
        BUNUSED(z);
        return ((Float)((x - basecx) * cxx + (y - basecy) * cxy));
    }
    // 3-d coordinate to 2-d projection (y).
    Float   w3wcy(Float x, Float y, Float z)
    { 
        return ((Float)((x - basecx) * cyx + (y - basecy) * cyy + (z - ranmi) * cyz));
    }

    // Draws a line segment from (x1, y1) to (x2, y2).
    void    pljoin(Float x1, Float y1, Float x2, Float y2)
    {
        if(error == 1) return;

        movwor(x1, y1);
        drawor(x2, y2);
    }

    // Move to physical coordinates (x,y).
    void    movphy(SInt32 x, SInt32 y)    { currx = x; curry = y;               }

    // Draw to physical coordinates (x,y).
    void    draphy(SInt32 x, SInt32 y)
    {
        BArray<BPoint<SInt32> > line(2);

        line[0] = BPoint<SInt32>(currx, curry);
        line[1] = BPoint<SInt32>(x, y);
        polyLineClip(line, 2, clpxmi, clpxma, clpymi, clpyma);
    }

    // Move to world coordinates (x,y).
    void    movwor(Float x, Float y)    { currx = wcpcx(x); curry = wcpcy(y);   }

    // Draw to world coordinates (x,y).
    void    drawor(Float x, Float y)
    {
        BArray<BPoint<SInt32> > line(2);

        line[0] = BPoint<SInt32>(currx, curry);
        line[1] = BPoint<SInt32>(wcpcx(x), wcpcy(y));
        polyLineClip(line, 2, clpxmi, clpxma, clpymi, clpyma);
    }

    /* Draw polyline in physical coordinates. */
    void PolyLinePhys(SInt32*, SInt32*, SInt32);
    /* Draw polyline in world coordinates. */
    void PolyLineWord(Float*, Float*, SInt32);
    void PolyLineWord(const std::vector<Float>& x, const std::vector<Float>& y);
    void PolyLineWord(const BArray<Float>& x, const BArray<Float>& y);
    void PolyLineWord(const BDynamicArray<Float>& x, const BDynamicArray<Float>& y);

    /* Draws a tick parallel to x. */
    void plxtik(SInt32, SInt32, SInt32, SInt32);
    /* Draws a tick parallel to y.*/
    void plytik(SInt32, SInt32, SInt32, SInt32);
    /*Draws a slanting tick at position (mx,my) (measured in mm) of vector length (dx,dy). */
    void plstik(Float, Float, Float, Float);

    void    plpsty1(SInt32);
    void    spat(SInt32*, SInt32*, SInt32);

    void    pldtik(Float, Float, Float*, SInt32*);

    void    WarnMessage(const char*, ...);
    void    AbortMessage(const char*, ...);

    /* Searches string str for character chr (case insensitive). */
    bool    stsearch(const char*, int);


    void    PlotHistogram(SInt32 nbin, Float* x, Float* y, SInt32 flags);

private:

    SInt32  lineClip(BPoint<SInt32>& p1, BPoint<SInt32>& p2, SInt32 xmin, 
                     SInt32 xmax, SInt32 ymin, SInt32 ymax);
    void    polyLine(SInt32*, SInt32*, SInt32);
    void    dashLine(SInt32* x, SInt32* y);

    void    polyLineClip(BArray<BPoint<SInt32> >& pt, SInt32 npts, SInt32 xmin, 
                         SInt32 xmax, SInt32 ymin, SInt32 ymax);
    void    fillPolygonClip(SInt32*, SInt32*, SInt32, SInt32, SInt32, SInt32, SInt32);
    void    fillPolygon(BDynamicArray<BPoint<SInt32> >& pt);
    void    fillPolygonSoft(SInt32*, SInt32*, SInt32);
    void    addCoordinate(BDynamicArray<SInt32>& buffer, SInt32 xp1, SInt32 yp1);
    void    tran(SInt32*, SInt32*, Float, Float);
    void    buildList(BDynamicArray<SInt32>& buffer, SInt32 xp1, SInt32 yp1, 
                      SInt32 xp2, SInt32 yp2, SInt32 xp3, SInt32 yp3, SInt32 dinc);
    /* FROM DRAW 3D */

public:

    SInt32 pl3mode;	

    /* Light source for shading */
    Float xlight, ylight, zlight;
    SInt32 threedshading;

private:

    SInt32 mhi, xxhi, newhisize;
    SInt32 mlo, xxlo, newlosize;
    SInt32 count, vcount;

    BDynamicArray<SInt32> oldhiview; 
    BDynamicArray<SInt32> oldloview;
    BDynamicArray<SInt32> newhiview;
    BDynamicArray<SInt32> newloview;

    SInt32 lastx, lasty;

    SInt32 bufferleng, buffersize;

    /* 1 update view; 0 no update */
    SInt32 pl3upv;	

public:

    void plt3zz(SInt32 x0, SInt32 y0, SInt32 dx, SInt32 dy, SInt32 flag, 
                SInt32 *inition, Float *x, Float *y, Float **z, SInt32 nx, 
                SInt32 ny, BDynamicArray<SInt32>& u, BDynamicArray<SInt32>& v,
                BDynamicArray<Float>& c);

    void plgrid3(Float);

private:

    void plnxtv(SInt32*, SInt32*, Float*, SInt32, SInt32);
    void drawTop(SInt32*, SInt32*, Float*, SInt32, SInt32);
    void drawBottom(SInt32*, SInt32*, Float*, SInt32, SInt32);

    void savehipoint(SInt32, SInt32);
    void savelopoint(SInt32, SInt32);
    void swaphiview(void);
    void swaploview(void);
    SInt32 plabv(SInt32, SInt32, SInt32, SInt32, SInt32, SInt32);
    void pl3cut(SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32*, SInt32*);
    Float GetAngleToLight(Float*, Float*, Float*);
    void draw3d(SInt32, SInt32, SInt32, SInt32);

    /* FROM CONTOUR */

public:

    /* Font height for contour labels (normalized) */
    Float contlabel_size;
    /* Offset of label from contour line (if set to 0.0, labels are printed on the lines). */
    Float contlabel_offset;
    /* Spacing parameter for contour labels */
    Float contlabel_space;
    /* Activate labels, default off */
    SInt32 contlabel_active;

private:

    void plcntr(Float**, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, Float, SInt32*, SInt32*, SInt32*, SInt32, SInt32);
    void pldrawcn(Float**, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, Float, char*, SInt32, SInt32, SInt32*, SInt32*, SInt32*, SInt32*, SInt32*, SInt32, SInt32);
    void drawcontlabel(Float, Float, char*, Float*, SInt32*);

    void plfloatlabel(Float, char*);
    void plccal(Float**, Float, SInt32, SInt32, SInt32, SInt32, Float*);

public:

    void Contour(Float**, SInt32, SInt32, SInt32, SInt32,	SInt32, SInt32, Float*, SInt32, SInt32);
    void FillPolygon(SInt32 n, Float* x, Float* y);

    /* FROM SHADE */

public:

    Float *xg1, *yg1, **xg2, **yg2; 

private:

    SInt32 fillshade;
    Float int_val;
    SInt32 min_pts[4], max_pts[4];
    SInt32 pen_col_min, pen_col_max;
    SInt32 pen_wd_min, pen_wd_max;
    Float sh_max, sh_min;
    SInt32 min_points, max_points, n_point;

public:

    /* Shade */
    void Shade(Float**, SInt32 (*)(Float, Float), Float, Float, SInt32, SInt32, Float, Float, Float, Float, Float, Float, SInt32, Float, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32, SInt32);
    void draw_boundary(SInt32, Float*, Float*);

private:

    void exfill(SInt32(*)(Float, Float), SInt32, Float*, Float*);
    void big_recl(SInt32*, register SInt32, SInt32, SInt32, SInt32*, SInt32*);
    int find_interval(Float, Float, SInt32, SInt32, Float*);
    void poly(SInt32(*)(Float, Float), Float*, Float*, SInt32, SInt32, SInt32, SInt32);
    SInt32 plctestez(Float*, SInt32, SInt32, SInt32, SInt32, Float);

    void set_cond(register SInt32*, register Float*, register SInt32);
    void SetCondition(BArray<SInt32>& cond, BArray<Float>& a, SInt32 n);

    void extfunc(Float, Float, Float*, Float*, SInt32, SInt32, SInt32);

private:

    void bisect(SInt32(*)(Float, Float), SInt32, Float, Float, Float, Float, Float*, Float*);
    SInt32 plctest(Float*, Float);


    // FROM SYMBOL

public:

    void FontLoad(SInt32 fnt);

    /* Prints out "text" at world cooordinate (x,y). */
    void TextOutWord(Float, Float, Float, Float, Float,  char*);
    /* Prints out "text" at specified position relative to viewport */
    void plmtex(const char*, Float, Float, Float, const char*);
    void WriteSymbol(SInt32, SInt32, SInt32);
    SInt32 GetSymbol(SInt32 ifont, SInt32 code);

private:

    void plchar(signed char*, Float*, SInt32, SInt32, SInt32, SInt32, SInt32, 
                Float, Float, Float, Float*, Float*, Float*);
    /* Prints out a "string" at reference position with physical coordinates  (refx, refy). */
    void plstr(SInt32 base, Float *xform, SInt32 refx, 
               SInt32 refy, const char *string);
    /* Computes the length of a string in mm, including escape sequences. */
    Float plstrl(const char* text);
    void plarrows(Float*, Float*, Float*, Float*, SInt32, Float, Float, Float);
    SInt32 stindex(const char*, const char*);
    // Set character height.
    void schr(Float def, Float scale);

public:

    enum { AT_BOP, DRAWING, AT_EOP };

};


#endif // _B_PLOT_STREAM_H_
