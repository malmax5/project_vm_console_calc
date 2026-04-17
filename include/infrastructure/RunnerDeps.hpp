#pragma once

#include "core/Constants.hpp"
#include "core/ICalculator.hpp"
#include "core/IChecker.hpp"
#include "core/IParser.hpp"
#include "core/IPrinter.hpp"

#include <memory>
#include <string>

namespace app_calculator::infrastructure
{

struct ServerRunnerDeps
{
  public:
    std::shared_ptr<core::IPrinter> printer;
    std::unique_ptr<core::IChecker> checker;
    std::unique_ptr<core::ICalculator> calculator;
};

struct ConsoleRunnerDeps
{
  public:
    std::shared_ptr<core::IPrinter> printer;
    std::unique_ptr<core::IParser> parser;
    std::unique_ptr<core::IChecker> checker;
    std::unique_ptr<core::ICalculator> calculator;

    std::string inputJson;
};

struct ClientRunnerDeps
{
  public:
    std::shared_ptr<core::IPrinter> printer;
    std::unique_ptr<core::IParser> parser;
    std::string inputJson;
    std::string serverAddress;
    int timeoutMs = core::defaultTimeoutMs;
};

} // namespace app_calculator::infrastructure