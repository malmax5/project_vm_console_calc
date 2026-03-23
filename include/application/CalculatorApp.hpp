#pragma once

#include "core/IPrinter.hpp"

#include <memory>
#include <string>

namespace app_calculator
{

class CalculatorApp
{
  public:
    void run(int argc, char **argv);

  private:
    static std::string getResourcePath(const char *executablePath);

    std::shared_ptr<core::IPrinter> _printer;
};

} // namespace app_calculator
