/**********************************************************************

Filename    :   BException.h
Content     :   

Created     :   June 20, 2013
Authors     :   Boris Rayskiy

Copyright   :   (c) 2013

**********************************************************************/


#ifndef _B_EXCEPTION_H_
#define _B_EXCEPTION_H_


#include <exception>
#include <string>
#include <sstream>


namespace BoriSoft {
namespace util {


class BException : public std::exception
{

public:

    BException()
        : m_msg("Unknown Message")
    {}

    BException(std::string& msg)
        : m_msg(msg)
    {}

    virtual ~BException() throw() {};

    virtual const char* what() const throw()
    {
        return m_msg.c_str();
    }

private:

    std::string m_msg;
};


} // namespace util
} // namespace BoriSoft


#endif // _B_EXCEPTION_H_
