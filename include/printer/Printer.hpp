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

    Printer(const Printer &) = delete;
    Printer &operator=(Printer &) = delete;
    Printer(Printer &&) noexcept = delete;
    Printer &operator=(Printer &&) noexcept = delete;

    void printResult(long long result) const override;
    void printError(std::string_view message) const override;
    void printInfo(std::string_view message) const override;

  private:
    logger::ILogger &_logger;
};

} // namespace app_calculator::printer
