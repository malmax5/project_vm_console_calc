#pragma once

#include "models/CalculationTask.hpp"

namespace app_calculator::core
{

class ICalculator
{
  public:
    ICalculator() = default;
    virtual ~ICalculator() = default;

    ICalculator(const ICalculator &) = delete;
    ICalculator &operator=(const ICalculator &) = delete;
    ICalculator(ICalculator &&) noexcept = delete;
    ICalculator &operator=(ICalculator &&) noexcept = delete;

    virtual long long calculate(const models::CalculationTask &task) = 0;
};

} // namespace app_calculator::core
