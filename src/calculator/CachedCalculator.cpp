#include "calculator/CachedCalculator.hpp"

#include "core/Exceptions.hpp"
#include "models/Operations.hpp"

#include <algorithm>

namespace app_calculator::calculator
{

CachedCalculator::CachedCalculator(
    std::unique_ptr<core::ICalculator> calculator,
    std::shared_ptr<core::IRepository<models::Calculation>> repository)
    : _calculator(std::move(calculator)), _repository(repository)
{
}

long long CachedCalculator::calculate(const models::CalculationTask &task)
{
    long long result = 0;

    int64_t operandA = task.operands.at(0);
    std::optional<int64_t> operandB = std::nullopt;

    if (task.operands.size() > 1)
    {
        operandB = task.operands.at(1);
    }

    auto cachedResult = _repository->findResult(operandA, operandB, task.operation);
    if (cachedResult.has_value())
    {
        result = *cachedResult;

        return result;
    }

    models::Calculation entry;
    entry.operandA = operandA;
    entry.operandB = operandB;
    entry.operation = task.operation;
    entry.result = std::nullopt;

    try
    {
        result = _calculator->calculate(task);

        entry.result = result;
        entry.status = models::OperationStatus::success;
        _repository->add(entry);

        return result;
    }
    catch (const exceptions::CalculationException &e)
    {
        entry.status = e.getCode();
        _repository->add(entry);

        throw;
    }
    catch (...)
    {
        entry.status = models::OperationStatus::unknownError;
        _repository->add(entry);

        throw;
    }
}

} // namespace app_calculator::calculator
