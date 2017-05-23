/**********************************************************************

Filename    :   BPrintf.h
Content     :   

Created     :   June 15, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/

#ifndef _B_PRINTF_H_
#define _B_PRINTF_H_


#include <BTypes.h>
#include <BMemory.h>
#include <BStd.h>
#include <BPrintf.h>
#include <stdio.h>
#include <stdarg.h>
#ifndef __DARWIN__
#include <malloc.h>
#endif

#ifdef WIN32
#pragma warning(disable: 4996)
#endif


namespace BoriSoft {
namespace bstd {


class BPrintf
{

public:

    void Init(const char* FileName)
    {
        //brs::std::fopen(&PrintStream, FileName, "w");
        PrintStream = ::fopen(FileName, "w");
    }


    void Printf(const char* format, ...)
    {
        va_list list;

        SInt32  count;
        char*   msgPtr  = 0;
        UInt32  Size    = 64;
        do
        {
            Size <<= 1;
            BREALLOC(msgPtr, char, Size, BLINE, BFILE);
            //msgPtr = (char *)realloc(msgPtr, Size);

            va_start(list, format);
            //UInt32 count  = brs::std::vsnprintf(msgPtr, Size, Size, format, list);
            count  = ::vsnprintf(msgPtr, Size, format, list);
            va_end(list);
        } while (count == -1);

        fprintf(PrintStream, "%s", msgPtr);
        fflush(PrintStream);

        if (msgPtr)
        {
            BFREE(msgPtr);
            //free(msgPtr);
        }
    }


    void Printf(char* msgPtr)
    {
        fprintf(PrintStream, "%s", msgPtr);
        fflush(PrintStream);
    }


    void Close(void)
    {
        if (PrintStream)
        {
            fclose(PrintStream);
        }
    }

private:

    FILE* PrintStream;

}; 


} // namespace bstd
} // namespace BoriSoft


#endif // _B_PRINTF_H_
