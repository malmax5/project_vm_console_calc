#include "calculator/Calculator.hpp"

#include "core/Exceptions.hpp"

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
        if (task.operation == "sum")
        {
            return _mathLib->add(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == "sub")
        {
            return _mathLib->sub(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == "mul")
        {
            return _mathLib->mul(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == "div")
        {
            return _mathLib->div(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == "pow")
        {
            return _mathLib->pow(task.operands.at(0), task.operands.at(1));
        }
        if (task.operation == "fact")
        {
            return _mathLib->factorial(task.operands.at(0));
        }
    }
    catch (const pvm_math_lib::calculator_exceptions::CalculatorExceptionOverflow &e)
    {
        throw exceptions::CalculationException("Math Overflow: " + std::string(e.what()));
    }
    catch (const pvm_math_lib::calculator_exceptions::CalculatorExceptionDivideByZero &e)
    {
        throw exceptions::CalculationException("Math Error: Division by zero");
    }
    catch (const std::exception &e)
    {
        throw exceptions::CalculationException("Internal Math Error: " + std::string(e.what()));
    }

    throw exceptions::CalculationException();
}

} // namespace app_calculator::calculator
