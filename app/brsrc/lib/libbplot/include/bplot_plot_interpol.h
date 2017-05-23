/**********************************************************************

Filename    :   Interpol.h
Content     :   

Created     :   March 10, 2001
Authors     :   Boris Rayskiy

Copyright   :   (c) 2001-2009

**********************************************************************/

#include <BTypes.h>


using namespace BoriSoft;


/* Identity transformation. */
void pltr0(Float, Float, Float*, Float*, SInt32, SInt32);

void mypltr(Float, Float, Float*, Float*, SInt32, SInt32);


/* Does linear interpolation from singly dimensioned coord arrays. */
void pltr1(Float*, Float*, Float, Float, Float*, Float*, SInt32, SInt32);

/* Does linear interpolation from doubly dimensioned coord arrays */
/* (column dominant, as per normal C 2d arrays). */
void pltr2(Float*, Float*, Float, Float, Float*, Float*, SInt32, SInt32);