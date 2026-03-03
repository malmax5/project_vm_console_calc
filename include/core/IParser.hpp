#pragma once

#include "models/CalculationTask.hpp"
#include <string_view>

namespace app_calculator::core
{

class IParser
{
  public:
    virtual ~IParser() = default;

    virtual models::CalculationTask parse(std::string_view inputData) = 0;
};

} // namespace app_calculator::core
