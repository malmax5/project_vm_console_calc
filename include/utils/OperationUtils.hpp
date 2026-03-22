#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace app_calculator::utils::operations
{

std::string makeOperationKey(int64_t operandA, std::optional<int64_t> operandB,
                             std::string_view operation);

} // namespace app_calculator::utils::operations
