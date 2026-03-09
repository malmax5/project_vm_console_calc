#include "checker/Checker.hpp"
#include "core/Exceptions.hpp"
#include "models/CalculationTask.hpp"
#include <gtest/gtest.h>

using namespace app_calculator;

class CheckerTest : public ::testing::Test
{
  protected:
    checker::Checker app_checker;
};

TEST_F(CheckerTest, ValidTaskPasses)
{
    const models::CalculationTask task{"sum", {1, 2}};
    EXPECT_NO_THROW(app_checker.check(task));
}

TEST_F(CheckerTest, ThrowsOnUnknownOperation)
{
    const models::CalculationTask task{"sqrt", {16}};
    EXPECT_THROW(app_checker.check(task), exceptions::ValidationException);
}

TEST_F(CheckerTest, ThrowsOnMissingArguments)
{
    const models::CalculationTask task{"sum", {0}};
    EXPECT_THROW(app_checker.check(task), exceptions::ValidationException);
}
