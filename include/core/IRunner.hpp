#pragma once

#include <string_view>

namespace app_calculator::core
{

class IRunner
{
  public:
    virtual ~IRunner();

    virtual void run(std::string_view jsonInput) = 0;
};

} // namespace app_calculator::core
