#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace app_calculator::models
{

enum class OperationStatus : int
{
    SUCCESS = 0,
    DIVISION_BY_ZERO = 1,
    OVERFLOW = 2,
    INVALID_OPERANDS = 3,
    UNKNOWN_ERROR = 4
};

struct Calculation
{
public:
    int64_t operandA;
    std::optional<int64_t> operandB;
    std::string operation;
    std::optional<int64_t> result;
    OperationStatus status;
    std::string createdAt;
};

} // namespace app_calculator::models
