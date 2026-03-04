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
    auto it = _operations.find({task.operation, 0});

    if (it == _operations.end())
    {
        throw exceptions::ValidationException("Unknown operation: " + task.operation);
    }

    if (task.operands.size() < it->expectedArgs)
    {
        throw exceptions::ValidationException("Operation '" + it->name + "' requires at least " +
                                              std::to_string(it->expectedArgs) + " operands");
    }
}

} // namespace app_calculator::checker
