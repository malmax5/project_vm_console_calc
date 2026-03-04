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

void Printer::print_result(long long result) const
{
    _logger.info("Calculation Result: " + std::to_string(result));
}

void Printer::print_error(std::string_view message) const
{
    _logger.error(message);
}

void Printer::print_info(std::string_view message) const
{
    _logger.debug(message);
}

} // namespace app_calculator::printer
