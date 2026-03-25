#include "calculator/Calculator.hpp"

#include "core/Exceptions.hpp"
#include "models/Operations.hpp"

namespace app_calculator::calculator
{

Calculator::Calculator() : _mathLib(std::make_unique<pvm_math_lib::Calculator>())
{
}

Calculator::~Calculator()
{
}

long long Calculator::calculate(const models::CalculationTask &task)
{
    try
    {
        if (task.operation == models::operations::sum)
        {
            return _mathLib->add(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == models::operations::sub)
        {
            return _mathLib->sub(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == models::operations::mul)
        {
            return _mathLib->mul(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == models::operations::div)
        {
            return _mathLib->div(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == models::operations::pow)
        {
            return _mathLib->pow(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == models::operations::fact)
        {
            return _mathLib->factorial(task.operands.at(0));
        }
    }
    catch (const pvm_math_lib::calculator_exceptions::CalculatorExceptionOverflow &e)
    {
        throw exceptions::CalculationException("Math Overflow: " + std::string(e.what()),
                                               models::OperationStatus::overflow);
    }
    catch (const pvm_math_lib::calculator_exceptions::CalculatorExceptionDivideByZero &e)
    {
        throw exceptions::CalculationException("Math Error: Division by zero",
                                               models::OperationStatus::divisionByZero);
    }
    catch (const pvm_math_lib::calculator_exceptions::CalculatorExceptionInvalidOperands &e)
    {
        throw exceptions::CalculationException(e.what(), models::OperationStatus::invalidOperands);
    }
    catch (const std::exception &e)
    {
        throw exceptions::CalculationException("Internal Math Error: " + std::string(e.what()),
                                               models::OperationStatus::unknownError);
    }

    throw exceptions::CalculationException();
}

} // namespace app_calculator::calculator
