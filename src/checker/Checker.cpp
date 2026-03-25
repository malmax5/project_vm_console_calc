#include "checker/Checker.hpp"

#include "core/Exceptions.hpp"
#include "models/Operations.hpp"

namespace app_calculator::checker
{

Checker::Checker()
{
}

Checker::~Checker()
{
}

void Checker::check(const models::CalculationTask &task)
{
    auto itOperation = models::operations::operationsInfo.find(task.operation);

    if (itOperation == models::operations::operationsInfo.end())
    {
        throw exceptions::ValidationException("Unknown operation: " + task.operation);
    }

    if (task.operands.size() < itOperation->second.expectedArgs)
    {
        throw exceptions::ValidationException(
            "Operation '" + std::string(itOperation->second.name) + "' requires at least " +
            std::to_string(itOperation->second.expectedArgs) + " operands");
    }
}

} // namespace app_calculator::checker
