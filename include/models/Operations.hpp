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

inline const std::set<models::OperationInfo> operationsInfo = {{sum, 2}, {sub, 2}, {mul, 2},
                                                               {div, 2}, {pow, 2}, {fact, 1}};

} // namespace app_calculator::models::operations
