#pragma once

#include "core/IPrinter.hpp"
#include "logger/ILogger.hpp"

#include <memory>

namespace app_calculator::printer
{

class Printer : public core::IPrinter
{
  public:
    Printer();
    ~Printer() override;

    void print_result(long long result) const override;
    void print_error(std::string_view message) const override;
    void print_info(std::string_view message) const override;

  private:
    logger::ILogger& _logger;
};

} // namespace app_calculator::printer
