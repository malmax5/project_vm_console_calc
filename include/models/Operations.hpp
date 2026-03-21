#pragma once

#include "models/OperationInfo.hpp"

#include <set>
#include <string_view>

namespace app_calculator::models::operations
{

inline constexpr std::string_view sum = "sum";
inline constexpr std::string_view sub = "sub";
inline constexpr std::string_view mul = "mul";
inline constexpr std::string_view div = "div";
inline constexpr std::string_view pow = "pow";
inline constexpr std::string_view fact = "fact";

inline const std::set<models::OperationInfo> operationsInfo = {
    {.name = sum, .expectedArgs = 2, .isCommutative = true},
    {.name = sub, .expectedArgs = 2, .isCommutative = false},
    {.name = mul, .expectedArgs = 2, .isCommutative = true},
    {.name = div, .expectedArgs = 2, .isCommutative = false},
    {.name = pow, .expectedArgs = 2, .isCommutative = false},
    {.name = fact, .expectedArgs = 1, .isCommutative = false}};

} // namespace app_calculator::models::operations
