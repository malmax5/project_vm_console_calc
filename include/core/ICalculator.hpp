#pragma once

#include "models/CalculationTask.hpp"

namespace app_calculator::core
{

class ICalculator
{
public:
    virtual ~ICalculator() = default;

    virtual long long calculate(const models::CalculationTask& task) = 0;
};

} // namespace app_calculator::core
