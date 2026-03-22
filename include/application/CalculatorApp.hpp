#pragma once

#include <string>

namespace app_calculator
{

class CalculatorApp
{
  public:
    static void run(int argc, char **argv);

  private:
    static std::string getResourcePath(const char *executablePath);
};

} // namespace app_calculator
