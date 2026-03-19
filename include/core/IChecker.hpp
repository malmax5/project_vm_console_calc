#pragma once

#include "models/CalculationTask.hpp"

namespace app_calculator::core
{

class IChecker
{
  public:
    IChecker() = default;
    virtual ~IChecker() = default;

    IChecker(const IChecker &) = default;
    IChecker &operator=(const IChecker &) = default;
    IChecker(IChecker &&) noexcept = default;
    IChecker &operator=(IChecker &&) noexcept = default;

    virtual void check(const models::CalculationTask &task) = 0;
};

} // namespace app_calculator::core
