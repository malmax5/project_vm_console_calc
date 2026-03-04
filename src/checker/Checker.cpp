#include "checker/Checker.hpp"

#include "core/Exceptions.hpp"

namespace app_calculator::checker
{

Checker::Checker()
{
    _operations = {{"sum", 2}, {"sub", 2}, {"mul", 2}, {"div", 2}, {"pow", 2}, {"fact", 2}};
}

Checker::~Checker()
{
}

void Checker::check(const models::CalculationTask &task)
{
    auto itOperation = _operations.find({task.operation, 0});

    if (itOperation == _operations.end())
    {
        throw exceptions::ValidationException("Unknown operation: " + task.operation);
    }

    if (task.operands.size() < itOperation->expectedArgs)
    {
        throw exceptions::ValidationException(
            "Operation '" + itOperation->name + "' requires at least " +
            std::to_string(itOperation->expectedArgs) + " operands");
    }
}

} // namespace app_calculator::checker
