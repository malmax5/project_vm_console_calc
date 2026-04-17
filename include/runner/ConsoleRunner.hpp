#pragma once

#include "core/IRunner.hpp"
#include "infrastructure/RunnerDeps.hpp"

#include <memory>

namespace app_calculator::runner
{

class ConsoleRunner final : public core::IRunner
{
  public:
    explicit ConsoleRunner(infrastructure::ConsoleRunnerDeps &deps);
    ~ConsoleRunner() override;

    ConsoleRunner(const ConsoleRunner &) = delete;
    ConsoleRunner &operator=(const ConsoleRunner &) = delete;
    ConsoleRunner(ConsoleRunner &&) noexcept = default;
    ConsoleRunner &operator=(ConsoleRunner &&) noexcept = default;

    void run() override;

  private:
    std::unique_ptr<core::IParser> _parser;
    std::unique_ptr<core::IChecker> _checker;
    std::unique_ptr<core::ICalculator> _calculator;
    std::shared_ptr<core::IPrinter> _printer;

    std::string _inputJson;
};

} // namespace app_calculator::runner
