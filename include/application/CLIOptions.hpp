#pragma once

#include "core/Constants.hpp"
#include "models/CalculationTask.hpp"

#include <string>
#include <vector>

namespace app_calculator
{

enum class AppMode
{
  unknown,
  server,
  console,
  client
};

struct CLIOptions
{
  public:
  AppMode mode = AppMode::unknown;
  std::string configPath = core::configPath;
  std::string address;
  int timeoutMs = core::defaultTimeoutMs;
  std::string inputJson;
  bool verbose = false;

  static CLIOptions parse(int argc, char **argv);
};

} // namespace app_calculator
