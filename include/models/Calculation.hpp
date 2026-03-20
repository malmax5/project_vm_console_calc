#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace app_calculator::models
{

enum class OperationStatus : int
{
    success = 0,
    divisionByZero = 1,
    overflow = 2,
    invalidOperands = 3,
    unknownError = 4
};

struct Calculation
{
  public:
    int64_t operandA{0};
    std::optional<int64_t> operandB{std::nullopt};
    std::string operation;
    std::optional<int64_t> result{std::nullopt};
    OperationStatus status{OperationStatus::unknownError};
    std::string createdAt;
};

} // namespace app_calculator::models
