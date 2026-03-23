#include "utils/OperationUtils.hpp"

#include "models/Operations.hpp"

#include <algorithm>
#include <stdexcept>

namespace app_calculator::utils::operations
{

std::string makeOperationKey(int64_t operandA, std::optional<int64_t> operandB,
                             std::string_view operation)
{
    std::string key = std::string(operation) + ":";

    const auto &itOperation = models::operations::operationsInfo.find({operation});
    if (itOperation == models::operations::operationsInfo.end())
    {
        throw std::runtime_error("Critical: Operation " + std::string(operation) +
                                 " not found in metadata. Cache key generation failed.");
    }

    if (itOperation->second.isCommutative)
    {
        key = key + (operandB.has_value() ? std::to_string(std::min(operandA, *operandB)) + ":" +
                                                std::to_string(std::max(operandA, *operandB))
                                          : std::to_string(operandA));
    }
    else
    {
        key =
            key + (operandB.has_value() ? std::to_string(operandA) + ":" + std::to_string(*operandB)
                                        : std::to_string(operandA));
    }

    return key;
}

} // namespace app_calculator::utils::operations
