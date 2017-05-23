/**********************************************************************

Filename    :   BPlotSymbol.h
Content     :   

Created     :   June 15, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/


#ifndef _B_PLOT_SYMBOL_H_
#define _B_PLOT_SYMBOL_H_


#include <BTypes.h>
#include <BMemory.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <vector>


#define PLPLOT5_FONTS


using namespace BoriSoft;


class BPlotSymbol
{

public:

    enum
    {
        MAXSTR	= 300,
        STLEN   = 250,
    };


public:

    BPlotSymbol();
    ~BPlotSymbol() { Release(); }

    // Loads either the standard or extended font.
    void    Init(SInt32);
    SInt32  GetSymbol(SInt32 ifont, SInt32 code);
  
    // Set character height.
    void    schr(Float, Float);
    SInt32  plcvec(SInt32, signed char**);
    void    pldeco(short int **symbol, SInt32 *length, const char *text, SInt32 ifont);
    void    Release(void);

private:
   
    SInt32  strpos(char*, int);

private:

    std::vector<std::string>    XFONT;
    std::vector<std::string>    SFONT;

    SInt32                      numberfonts;
    SInt32                      numberchars;
    short int*                  fntlkup;

    short                       fontloaded;
    short int*                  fntindx;
    signed char*                fntbffr;
    short int                   indxleng;

    short                       symbol_buffer[MAXSTR];
    signed char                 xygrid[STLEN];  
};


#endif // _B_PLOT_SYMBOL_H_
