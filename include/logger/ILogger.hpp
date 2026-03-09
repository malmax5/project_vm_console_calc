#pragma once

#include <string_view>

namespace app_calculator::logger
{

class ILogger
{
  public:
    ILogger() = default;
    virtual ~ILogger() = default;

    ILogger(const ILogger &) = delete;
    ILogger &operator=(const ILogger &) = delete;
    ILogger(ILogger &&) noexcept = delete;
    ILogger &operator=(ILogger &&) noexcept = delete;

    virtual void debug(std::string_view message) = 0;
    virtual void info(std::string_view message) = 0;
    virtual void warn(std::string_view message) = 0;
    virtual void error(std::string_view message) = 0;
};

} // namespace app_calculator::logger
