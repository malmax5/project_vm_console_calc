#pragma once

#include "core/ICalculator.hpp"
#include "core/IChecker.hpp"
#include "core/IParser.hpp"
#include "core/IPrinter.hpp"

#include <memory>

namespace app_calculator::infrastructure
{

struct AppContext
{
  public:
    std::shared_ptr<core::IPrinter> printer;
};

} // namespace app_calculator::infrastructure
