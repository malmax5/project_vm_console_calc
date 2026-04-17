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
    std::shared_ptr<core::IPrinter> printer;
};

} // namespace app_calculator::infrastructure
