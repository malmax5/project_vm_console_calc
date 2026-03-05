#include "core/Exceptions.hpp"
#include "models/CalculationTask.hpp"
#include "parser/JsonParser.hpp"
#include <gtest/gtest.h>

using namespace app_calculator;

class JsonParserTest : public ::testing::Test
{
  protected:
    parser::JsonParser app_parser;
};

TEST_F(JsonParserTest, ParsesValidJson)
{
    const std::string validInput = R"({"operation": "sum", "operands": [10, 20]})";

    EXPECT_NO_THROW({
        const auto task = app_parser.parse(validInput);
        EXPECT_EQ(task.operation, "sum");
        EXPECT_EQ(task.operands.size(), 2);
    });
}

TEST_F(JsonParserTest, ThrowsOnInvalidJsonSyntax)
{
    const std::string brokenJson = R"({"operation": "sum")";
    EXPECT_THROW(app_parser.parse(brokenJson), exceptions::ParserException);
}

TEST_F(JsonParserTest, ThrowsOnMissingRequiredFields)
{
    const std::string missingField = R"({"operands": [1.0, 2.0]})";
    EXPECT_THROW(app_parser.parse(missingField), exceptions::ParserException);
}

TEST_F(JsonParserTest, ThrowsOnTypeMismatch)
{
    const std::string wrongType = R"({"operation": "sum", "operands": "not_a_list"})";
    EXPECT_THROW(app_parser.parse(wrongType), exceptions::ParserException);
}
