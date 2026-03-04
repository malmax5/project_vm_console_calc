#pragma once

#include "models/CalculationTask.hpp"

namespace app_calculator::core
{

class IChecker
{
  public:
    virtual ~IChecker() = default;

    virtual void check(const models::CalculationTask &task) = 0;
};

} // namespace app_calculator::core
