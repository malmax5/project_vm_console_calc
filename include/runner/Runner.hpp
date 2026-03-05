#pragma once

#include "core/ICalculator.hpp"
#include "core/IChecker.hpp"
#include "core/IParser.hpp"
#include "core/IPrinter.hpp"
#include "core/IRunner.hpp"

#include <memory>

namespace app_calculator::runner
{

class Runner : public core::IRunner
{
  public:
    Runner();
    Runner(std::unique_ptr<core::IParser> parser, std::unique_ptr<core::IChecker> checker,
           std::unique_ptr<core::ICalculator> calculator, std::unique_ptr<core::IPrinter> printer);
    ~Runner() override;

    Runner(const Runner &) = delete;
    Runner &operator=(const Runner &) = delete;
    Runner(Runner &&) noexcept = delete;
    Runner &operator=(Runner &&) noexcept = delete;

    void run(std::string_view jsonInput) override;

  private:
    std::unique_ptr<core::IParser> _parser;
    std::unique_ptr<core::IChecker> _checker;
    std::unique_ptr<core::ICalculator> _calculator;
    std::unique_ptr<core::IPrinter> _printer;
};

} // namespace app_calculator::runner
