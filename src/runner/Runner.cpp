#include "runner/Runner.hpp"

#include "calculator/Calculator.hpp"
#include "checker/Checker.hpp"
#include "core/Exceptions.hpp"
#include "parser/JsonParser.hpp"
#include "printer/Printer.hpp"

#include "string_view"

namespace app_calculator::runner
{

Runner::Runner()
    : _parser(std::make_unique<parser::JsonParser>()),
      _checker(std::make_unique<checker::Checker>()),
      _calculator(std::make_unique<calculator::Calculator>()),
      _printer(std::make_unique<printer::Printer>())
{
}

Runner::Runner(std::unique_ptr<core::IParser> parser, std::unique_ptr<core::IChecker> checker,
               std::unique_ptr<core::ICalculator> calculator,
               std::shared_ptr<core::IPrinter> printer)
    : _parser(std::move(parser)), _checker(std::move(checker)), _calculator(std::move(calculator)),
      _printer(printer)
{
}

Runner::~Runner()
{
}

void Runner::run(int argc, char **argv)
{
    if (argc <= 1)
    {
        _printer->printWarn("No arguments provided.");
        return;
    }

    std::string_view jsonInput = argv[1];

    try
    {
        _printer->printInfo("Starting calculation task...");

        auto task = _parser->parse(jsonInput);

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
