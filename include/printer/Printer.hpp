#pragma once

#include "core/IPrinter.hpp"
#include "logger/ILogger.hpp"

#include <memory>

namespace app_calculator::printer
{

class Printer final : public core::IPrinter
{
  public:
    Printer();
    Printer(std::shared_ptr<logger::ILogger> logger);
    ~Printer() override;

    Printer(const Printer &) = delete;
    Printer &operator=(Printer &) = delete;
    Printer(Printer &&) noexcept = default;
    Printer &operator=(Printer &&) noexcept = default;

    void printResult(long long result) const override;
    void printError(std::string_view message) const override;
    void printWarn(std::string_view message) const override;
    void printInfo(std::string_view message) const override;

  private:
    std::shared_ptr<logger::ILogger> _logger;
};

} // namespace app_calculator::printer
