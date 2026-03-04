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
    ParserException() : AppException("Parser Error: Unknown issue.")
    {
    }

    explicit ParserException(const std::string &msg) : AppException("Parser Error" + msg)
    {
    }
};

class ValidationException : public AppException
{
  public:
    ValidationException() : AppException("Validation Error: Unknown issue.")
    {
    }

    explicit ValidationException(const std::string &msg) : AppException("Validation Error: " + msg)
    {
    }
};

} // namespace app_calculator::exceptions
