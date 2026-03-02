#pragma once

#include <string_view>

namespace app_calculator::logger
{

class ILogger
{
public:
    virtual ~ILogger() = default;

    virtual void debug(std::string_view message) = 0;
    virtual void info(std::string_view message) = 0;
    virtual void warn(std::string_view message) = 0;
    virtual void error(std::string_view message) = 0;
};

}
