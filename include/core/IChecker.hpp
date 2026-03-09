#pragma once

#include "models/CalculationTask.hpp"

namespace app_calculator::core
{

class IChecker
{
  public:
    IChecker() = default;
    virtual ~IChecker() = default;

    IChecker(const IChecker &) = delete;
    IChecker &operator=(const IChecker &) = delete;
    IChecker(IChecker &&) noexcept = delete;
    IChecker &operator=(IChecker &&) noexcept = delete;

    virtual void check(const models::CalculationTask &task) = 0;
};

} // namespace app_calculator::core
