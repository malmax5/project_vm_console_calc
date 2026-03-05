#include "printer/Printer.hpp"

#include "logger/Logger.hpp"

#include <string>

namespace app_calculator::printer
{

Printer::Printer() : _logger(logger::Logger::instance())
{
}

Printer::~Printer()
{
}

void Printer::printResult(long long result) const
{
    _logger.info("Calculation Result: " + std::to_string(result));
}

void Printer::printError(std::string_view message) const
{
    _logger.error(message);
}

void Printer::printInfo(std::string_view message) const
{
    _logger.debug(message);
}

} // namespace app_calculator::printer
