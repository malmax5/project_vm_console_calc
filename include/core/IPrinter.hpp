#pragma once

#include <string_view>

namespace app_calculator::core
{

class IPrinter
{
  public:
    IPrinter() = default;
    virtual ~IPrinter() = default;

    IPrinter(const IPrinter &) = delete;
    IPrinter &operator=(const IPrinter &) = delete;
    IPrinter(IPrinter &&) noexcept = default;
    IPrinter &operator=(IPrinter &&) noexcept = default;

    virtual void printResult(long long result) const = 0;
    virtual void printError(std::string_view message) const = 0;
    virtual void printWarn(std::string_view message) const = 0;
    virtual void printInfo(std::string_view message) const = 0;
};

} // namespace app_calculator::core
