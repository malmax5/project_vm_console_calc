#pragma once

#include "core/IChecker.hpp"
#include "models/OperationInfo.hpp"

#include <set>
#include <string_view>

namespace app_calculator::checker
{

class Checker : public core::IChecker
{
  public:
    Checker();
    ~Checker() override;

    void check(const models::CalculationTask &task) override;
};

} // namespace app_calculator::checker
