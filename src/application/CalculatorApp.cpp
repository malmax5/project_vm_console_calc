#include "application/CalculatorApp.hpp"

#include "core/Exceptions.hpp"
#include "core/IRunner.hpp"
#include "infrastructure/ComponentFactory.hpp"

#include <filesystem>

namespace app_calculator
{

void CalculatorApp::run(int argc, char **argv)
{
    try
    {
        std::string configPath = getResourcePath(argv[0]);
        auto components = infrastructure::ComponentFactory::createProductionComponents(configPath);
        _printer = components.printer;

        _printer->printInfo("Application started");
        _printer->printInfo("Target config path: " + configPath);

        std::unique_ptr<core::IRunner> runner;

        if (argc > 1 && std::string(argv[1]) == "--server")
        {
            _printer->printInfo("Mode: SERVER");
            runner = infrastructure::ComponentFactory::createServerRunner(configPath);
        }
        else if (argc > 1 && std::string(argv[1]) == "--console")
        {
            _printer->printInfo("Mode: CONSOLE");
            std::string inputJson = std::string(argv[2]);
            runner = infrastructure::ComponentFactory::createConsoleRunner(configPath, inputJson);
        }
        else
        {
            throw exceptions::ConfigException("Invalid mode specified. Use --server or --console.");
        }

        runner->run();
    }
    catch (const std::exception &e)
    {
        if (_printer)
        {
            _printer->printError("Initialization failed: " + std::string(e.what()));
        }

        throw;
    }
    catch (...)
    {
        if (_printer)
        {
            _printer->printError("Initialization failed: Unknown error");
        }

        throw;
    }
}

std::string CalculatorApp::getResourcePath(const char *executablePath)
{
    const std::string sysConfigPath = "/etc/calculator/config.json";
    if (std::filesystem::exists(sysConfigPath))
    {
        try
        {
            return std::filesystem::canonical(sysConfigPath).string();
        }
        catch (const std::filesystem::filesystem_error &)
        {
            return sysConfigPath;
        }
    }

    throw exceptions::ConfigException("Configuration file not found at: " + sysConfigPath);
}

} // namespace app_calculator
