#pragma once

#include <string_view>

namespace app_calculator::core
{

class IPrinter
{
  public:
    virtual ~IPrinter() = default;

    virtual void print_result(long long result) const = 0;
    virtual void print_error(std::string_view message) const = 0;
    virtual void print_info(std::string_view message) const = 0;
};

} // namespace app_calculator::core
