#pragma once

#include "core/ICalculator.hpp"
#include "core/IChecker.hpp"
#include "core/IParser.hpp"
#include "core/IPrinter.hpp"

#include <memory>

namespace app_calculator::infrastructure
{

struct AppComponents
{
  public:
    std::unique_ptr<core::IParser> parser;
    std::unique_ptr<core::IChecker> checker;
    std::unique_ptr<core::IPrinter> printer;
    std::unique_ptr<core::ICalculator> calculator;
};

class ComponentFactory
{
  public:
    static AppComponents createProductionComponents(const std::string &configPath);
};

} // namespace app_calculator::infrastructure
