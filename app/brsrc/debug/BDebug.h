/**********************************************************************

Filename    :   BDebug.h
Content     :   

Created     :   June 15, 2009
Authors     :   Boris Rayskiy

Copyright   :   (c) 2009

**********************************************************************/

#ifndef _B_DEBUG_H_
#define _B_DEBUG_H_


#include <BTypes.h>
//#include <BArray.h>
#include <string.h>
#include <stdarg.h>


#ifdef WIN32
#include <windows.h>
#endif


#ifdef WIN32
#define B_DEBUG_TRAP    do { BASM int 3          } while (0)
#else
#define B_DEBUG_TRAP    do { BASM("int $3\n\t"); } while(0)
#endif

//#define B_DEBUG_TRAP do { __debugbreak();     } while(0) // __cplusplus_cli
//#define B_DEBUG_TRAP do { *((int *) 0) = 1;   } while(0) // 


#ifdef _DEBUG
#define BASSERT(p) do { if (!(p))  { B_DEBUG_TRAP; } } while(0)
#else
#define BASSERT(p) (0)
#endif


/*
enum BMessageType
{
    Message_Note,
    Message_Info,
    Message_Warning,    
    Message_Error,      
    Message_Assert,
};


class BDebug
{

public:

    static void Message(BMessageType msgType, const char *pformat, ...)
    {
        enum { BUFFERSIZE = 4096 };

        BArray<char> buffer(4096);

        va_list  argList;
        va_start(argList, pformat);

        vsprintf_s(&buffer[0], BUFFERSIZE, pformat, argList);

        switch(msgType)
        {
        case Message_Info:     
            strcpy_s(&buffer[0], BUFFERSIZE, "Info: ");     
            break;
        case Message_Error:     
            strcpy_s(&buffer[0], BUFFERSIZE, "Error: ");     
            break;
        case Message_Warning:
            strcpy_s(&buffer[0], BUFFERSIZE, "Warning: ");
            break;
        case Message_Assert:
            strcpy_s(&buffer[0], BUFFERSIZE, "Assert: ");
            break;
        case Message_Note:
            buffer[0] = 0;
            break;
        }
      
        ::OutputDebugStringA(&buffer[0]);
        //fputs(&buffer[0], stdout);

        va_end(argList);
    }

};
*/

#endif // _B_DEBUG_H_
