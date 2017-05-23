/**********************************************************************

Filename    :   BPlotStyle.h
Content     :   

Created     :   March 10, 2001
Authors     :   Boris Rayskiy

Copyright   :   (c) 2001-2009

**********************************************************************/

class CLine 
{

public:
    
    SInt32 nels;
    SInt32 mark[4];
    SInt32 space[4];

}; 


class CPattern 
{

public:

    SInt32 nlines;		/* Number of lines in pattern (1 or 2) */
    SInt32 inc[2];		/* Inclination 10 ths of degrees */
    SInt32 del[2];		/* Spacing for each line */

};
