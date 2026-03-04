#pragma once

#include "core/ICalculator.hpp"

#include <pvm_math_lib/calculator_math.hpp>

#include <memory>

namespace app_calculator::calculator
{

class Calculator : public core::ICalculator
{
  public:
    ~Calculator() override;

    long long calculate(const models::CalculationTask &task) override;

  private:
    std::unique_ptr<pvm_math_lib::ICalculator> _mathLib;
};

} // namespace app_calculator::calculator
