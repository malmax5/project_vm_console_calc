#pragma once

#include <string>
#include <stdexcept>

namespace app_calculator::exceptions
{

class AppException: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class ParserExceptions: public AppException
{
public:
    ParserExceptions()
        : AppException("App Error: Parser exception is occured.")
    {

    }

    ParserExceptions(const std::string& msg)
        : AppException(msg)
    {

    }
};

}
