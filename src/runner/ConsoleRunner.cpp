#include "runner/ConsoleRunner.hpp"

#include "calculator/Calculator.hpp"
#include "checker/Checker.hpp"
#include "core/Exceptions.hpp"
#include "parser/JsonParser.hpp"
#include "printer/Printer.hpp"

#include "string_view"

namespace app_calculator::runner
{

ConsoleRunner::ConsoleRunner(infrastructure::ConsoleRunnerDeps &deps)
    : _parser(std::move(deps.parser)), _checker(std::move(deps.checker)),
      _calculator(std::move(deps.calculator)), _printer(deps.printer), _inputJson(deps.inputJson)
{
}

ConsoleRunner::~ConsoleRunner()
{
}

void ConsoleRunner::run()
{
    try
    {
        _printer->printInfo("Starting calculation task...");

        auto task = _parser->parse(_inputJson);

        _checker->check(task);

        long long result = _calculator->calculate(task);

        _printer->printResult(result);
    }
    catch (const exceptions::AppException &e)
    {
        _printer->printError(e.what());
    }
    catch (const std::exception &e)
    {
        _printer->printError("Unexpected system error: " + std::string(e.what()));
    }
}

} // namespace app_calculator::runner
