#pragma once

#include "core/ICalculator.hpp"
#include "core/IChecker.hpp"
#include "core/IParser.hpp"
#include "core/IPrinter.hpp"
#include "core/IRunner.hpp"

#include <memory>

namespace app_calculator::infrastructure
{

struct AppComponents
{
  public:
    std::unique_ptr<core::IParser> parser;
    std::unique_ptr<core::IChecker> checker;
    std::shared_ptr<core::IPrinter> printer;
    std::unique_ptr<core::ICalculator> calculator;
};

class ComponentFactory
{
  public:
    static AppComponents createProductionComponents(const std::string &configPath);
    static std::unique_ptr<core::IRunner> createConsoleRunner(const std::string &configPath,
                                                              std::string &inputJson);
};

} // namespace app_calculator::infrastructure
