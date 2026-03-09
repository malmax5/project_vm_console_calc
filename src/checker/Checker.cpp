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
    auto itOperation = models::operations::operationsInfo.find({task.operation, 0});

    if (itOperation == models::operations::operationsInfo.end())
    {
        throw exceptions::ValidationException("Unknown operation: " + task.operation);
    }

    if (task.operands.size() < itOperation->expectedArgs)
    {
        throw exceptions::ValidationException(
            "Operation '" + std::string(itOperation->name) + "' requires at least " +
            std::to_string(itOperation->expectedArgs) + " operands");
    }
}

} // namespace app_calculator::checker
