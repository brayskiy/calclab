/**********************************************************************

Filename    :   BPlotException.h
Content     :   

Created     :   June 14, 2013
Authors     :   Boris Rayskiy

Copyright   :   (c) 2013

**********************************************************************/


#ifndef _B_PLOT_EXCEPTION_H_
#define _B_PLOT_EXCEPTION_H_


#include <BException.h>


using namespace BoriSoft;

namespace BoriSoft {
namespace util {

class BPlotException : public util::BException
{};


} // namespace util
} // namespace BoriSoft


#define THROW_BPLOT_EXCEPTION(msg) \
{                                  \
    std::ostringstream oss;        \
    oss << "BPlotException: ";     \
    oss << __FILE__ << ": ";       \
    oss << __LINE__ << " ";        \
    oss << msg;                    \
                                   \
    throw oss.str();               \
}


#endif // _B_PLOT_EXCEPTION_H_
