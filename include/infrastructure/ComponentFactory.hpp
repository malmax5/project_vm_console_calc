#pragma once

#include "infrastructure/AppContext.hpp"
#include "infrastructure/RunnerDeps.hpp"
#include "application/CLIOptions.hpp"

#include <memory>

namespace app_calculator::infrastructure
{
class ComponentFactory
{
  public:
    static AppContext createApplicationContext();
    static ConsoleRunnerDeps createConsoleRunnerComponents(const CLIOptions &options);
    static ServerRunnerDeps createServerRunnerComponents(const CLIOptions &options);
    static ClientRunnerDeps createClientRunnerComponents(const CLIOptions &options);
};

} // namespace app_calculator::infrastructure
