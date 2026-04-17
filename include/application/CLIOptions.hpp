#pragma once

#include "models/CalculationTask.hpp"

#include <string>
#include <vector>

namespace app_calculator
{

enum class AppMode
{
    Server,
    Console,
    Client
};

struct CLIOptions
{
public:
    AppMode mode = AppMode::Server;
    std::string configPath = "/etc/calculator/config.json";
    std::string serverAddress = "localhost:50051";
    int timeoutMs = 5000;

    std::string inputJson;

    bool verbose = false;

    static CLIOptions parse(int argc, char **argv);
};

} // namespace app_calculator
