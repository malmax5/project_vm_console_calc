#include "runner/ConsoleRunner.hpp"

#include "calculator/Calculator.hpp"
#include "checker/Checker.hpp"
#include "core/Exceptions.hpp"
#include "parser/JsonParser.hpp"
#include "printer/Printer.hpp"

#include "string_view"

namespace app_calculator::runner
{

ConsoleRunner::ConsoleRunner()
    : _parser(std::make_unique<parser::JsonParser>()),
      _checker(std::make_unique<checker::Checker>()),
      _calculator(std::make_unique<calculator::Calculator>()),
      _printer(std::make_unique<printer::Printer>())
{
}

ConsoleRunner::ConsoleRunner(std::unique_ptr<core::IParser> parser,
                             std::unique_ptr<core::IChecker> checker,
                             std::unique_ptr<core::ICalculator> calculator,
                             std::shared_ptr<core::IPrinter> printer, const std::string &inputJson)
    : _parser(std::move(parser)), _checker(std::move(checker)), _calculator(std::move(calculator)),
      _printer(printer), _inputJson(inputJson)
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
