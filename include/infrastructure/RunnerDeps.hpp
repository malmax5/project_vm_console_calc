#pragma once

#include "core/IParser.hpp"
#include "core/IChecker.hpp"
#include "core/IPrinter.hpp"
#include "core/ICalculator.hpp"

#include "models/CalculationResult.hpp"

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
    int timeoutMs;
    models::CalculationTask task;
};

} // namespace app_calculator::infrastructure