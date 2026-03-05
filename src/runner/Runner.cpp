#include "runner/Runner.hpp"

#include "calculator/Calculator.hpp"
#include "checker/Checker.hpp"
#include "core/Exceptions.hpp"
#include "parser/JsonParser.hpp"
#include "printer/Printer.hpp"

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
               std::unique_ptr<core::IPrinter> printer)
    : _parser(std::move(parser)), _checker(std::move(checker)), _calculator(std::move(calculator)),
      _printer(std::move(printer))
{
}

Runner::~Runner()
{
}

void Runner::run(std::string_view jsonInput)
{
    try
    {
        _printer->print_info("Starting calculation task...");

        auto task = _parser->parse(jsonInput);

        _checker->check(task);

        long long result = _calculator->calculate(task);

        _printer->print_result(result);
    }
    catch (const exceptions::AppException &e)
    {
        _printer->print_error(e.what());
    }
    catch (const std::exception &e)
    {
        _printer->print_error("Unexpected system error: " + std::string(e.what()));
    }
}

} // namespace app_calculator::runner
