#include "calculator/Calculator.hpp"
#include "core/Exceptions.hpp"
#include "models/CalculationTask.hpp"
#include <gtest/gtest.h>
#include <limits>

using namespace app_calculator;

class CalculatorTest : public ::testing::Test
{
  protected:
    calculator::Calculator app_calc;

    static constexpr long long maxLL = std::numeric_limits<long long>::max();
    static constexpr long long minLL = std::numeric_limits<long long>::min();
};

TEST_F(CalculatorTest, SimpleAddition)
{
    const models::CalculationTask task{"sum", {10, 5}};
    EXPECT_EQ(app_calc.calculate(task), 15);
}

TEST_F(CalculatorTest, HandlesMathLibDivideByZero)
{
    const models::CalculationTask task{"div", {10, 0}};
    EXPECT_THROW(app_calc.calculate(task), exceptions::CalculationException);
}

TEST_F(CalculatorTest, FactorialOfNegativeNumber)
{
    const models::CalculationTask task{"fact", {-5}};
    EXPECT_THROW(app_calc.calculate(task), exceptions::CalculationException);
}

TEST_F(CalculatorTest, PowerByNegativeExponent)
{
    const models::CalculationTask task{"pow", {5, -1}};
    EXPECT_THROW(app_calc.calculate(task), exceptions::CalculationException);
}

TEST_F(CalculatorTest, OverflowInAdd)
{
    const models::CalculationTask task{"add", {maxLL, 1}};
    EXPECT_THROW(app_calc.calculate(task), exceptions::CalculationException);
}

TEST_F(CalculatorTest, OverflowInSub)
{
    const models::CalculationTask task{"sub", {minLL, 1}};
    EXPECT_THROW(app_calc.calculate(task), exceptions::CalculationException);
}

TEST_F(CalculatorTest, OverflowInMul)
{
    const models::CalculationTask task{"mul", {maxLL, 2}};
    EXPECT_THROW(app_calc.calculate(task), exceptions::CalculationException);
}

TEST_F(CalculatorTest, OverflowInPower)
{
    const models::CalculationTask task{"pow", {2, 63}};

    EXPECT_THROW(app_calc.calculate(task), exceptions::CalculationException);
}

TEST_F(CalculatorTest, OverflowInFact)
{
    const long long maxLL = std::numeric_limits<long long>::max();
    const models::CalculationTask task{"fact", {21}};

    EXPECT_THROW(app_calc.calculate(task), exceptions::CalculationException);
}
