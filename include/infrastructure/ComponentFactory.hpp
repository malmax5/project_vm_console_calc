#pragma once

#include "infrastructure/AppContext.hpp"

#include <memory>

namespace app_calculator::infrastructure
{
class ComponentFactory
{
  public:
    static AppContext createProductionContext(const std::string &configPath);
};

} // namespace app_calculator::infrastructure
