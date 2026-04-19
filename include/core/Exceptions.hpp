#pragma once

#include "models/Calculation.hpp"

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

class CalculationException : public AppException
{
  public:
    CalculationException()
        : AppException("Calculation Error: Unknown issue."),
          _code(models::OperationStatus::unknownError)
    {
    }

    explicit CalculationException(const std::string &msg, models::OperationStatus code =
                                                              models::OperationStatus::unknownError)
        : AppException("Calculation Error: " + msg), _code(code)
    {
    }

    models::OperationStatus getCode() const
    {
        return _code;
    }

  private:
    models::OperationStatus _code;
};

class DatabaseException : public AppException
{
  public:
    DatabaseException() : AppException("Database Error: Unknown issue.")
    {
    }

    explicit DatabaseException(const std::string &msg) : AppException("Database Error: " + msg)
    {
    }
};

class ConnectionException : public DatabaseException
{
  public:
    ConnectionException() : DatabaseException("Connection failed.")
    {
    }

    explicit ConnectionException(const std::string &msg)
        : DatabaseException("Connection failed: " + msg)
    {
    }
};

class QueryException : public DatabaseException
{
  public:
    QueryException() : DatabaseException("Query execution failed.")
    {
    }

    explicit QueryException(const std::string &msg)
        : DatabaseException("Query execution failed: " + msg)
    {
    }
};

class ConfigException : public AppException
{
  public:
    ConfigException() : AppException("Configuration Error: Unknown issue.")
    {
    }

    explicit ConfigException(const std::string &msg) : AppException("Configuration Error: " + msg)
    {
    }
};

class NetworkException : public AppException
{
  public:
    NetworkException() : AppException("Network Error: Unknown issue.")
    {
    }

    explicit NetworkException(const std::string &msg) : AppException("Network Error: " + msg)
    {
    }
};

class GrpcException : public NetworkException
{
  public:
    GrpcException() : NetworkException("gRPC Error: Unknown issue.")
    {
    }

    explicit GrpcException(const std::string &msg) : NetworkException("gRPC Error: " + msg)
    {
    }
};

class NetworkTimeoutException : public NetworkException
{
  public:
    NetworkTimeoutException() : NetworkException("Network Timeout: Unknown issue.")
    {
    }

    explicit NetworkTimeoutException(const std::string &msg)
        : NetworkException("Network Timeout: " + msg)
    {
    }
};

} // namespace app_calculator::exceptions
