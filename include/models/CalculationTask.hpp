#pragma once

#include <string>
#include <vector>

namespace app_calculator::models
{

struct CalculationTask
{
public:
    std::string operation;
    std::vector<long long> operands;
};

} // namespace app_calculator::models
