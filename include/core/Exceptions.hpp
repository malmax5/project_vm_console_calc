#pragma once

#include <stdexcept>
#include <string>

namespace app_calculator::exceptions
{

class AppException : public std::runtime_error
{
  public:
    using std::runtime_error::runtime_error;
};

class ParserException : public AppException
{
  public:
    ParserException() : AppException("App Error: Parser exception is occured.")
    {
    }

    ParserException(const std::string &msg) : AppException(msg)
    {
    }
};

} // namespace app_calculator::exceptions
