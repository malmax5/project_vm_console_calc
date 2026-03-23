#pragma once

#include "models/OperationInfo.hpp"

#include <string_view>
#include <unordered_map>

namespace app_calculator::models::operations
{

inline constexpr std::string_view sum = "sum";
inline constexpr std::string_view sub = "sub";
inline constexpr std::string_view mul = "mul";
inline constexpr std::string_view div = "div";
inline constexpr std::string_view pow = "pow";
inline constexpr std::string_view fact = "fact";

inline const std::unordered_map<std::string_view, models::OperationInfo> operationsInfo = {
    {sum, {.name = sum, .expectedArgs = 2, .isCommutative = true}},
    {sub, {.name = sub, .expectedArgs = 2, .isCommutative = false}},
    {mul, {.name = mul, .expectedArgs = 2, .isCommutative = true}},
    {div, {.name = div, .expectedArgs = 2, .isCommutative = false}},
    {pow, {.name = pow, .expectedArgs = 2, .isCommutative = false}},
    {fact, {.name = fact, .expectedArgs = 1, .isCommutative = false}}};

} // namespace app_calculator::models::operations
