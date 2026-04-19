#pragma once

#include "core/IRunner.hpp"
#include "infrastructure/AppContext.hpp"
#include "infrastructure/RunnerDeps.hpp"

namespace app_calculator::infrastructure
{

class RunnerFactory
{
  public:
    static std::unique_ptr<core::IRunner> createServerRunner(ServerRunnerDeps &deps);
    static std::unique_ptr<core::IRunner> createConsoleRunner(ConsoleRunnerDeps &deps);
    static std::unique_ptr<core::IRunner> createClientRunner(ClientRunnerDeps &deps);
};

} // namespace app_calculator::infrastructure
