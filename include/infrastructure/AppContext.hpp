#pragma once

#include "core/IParser.hpp"
#include "core/IChecker.hpp"
#include "core/IPrinter.hpp"
#include "core/ICalculator.hpp"

#include <memory>

namespace app_calculator::infrastructure
{

struct AppContext
{
public:
    std::unique_ptr<core::IParser> parser;
    std::unique_ptr<core::IChecker> checker;
    std::shared_ptr<core::IPrinter> printer;
    std::unique_ptr<core::ICalculator> calculator;
}

} // namespace app_calculator::infrastructure
