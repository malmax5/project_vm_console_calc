#include "application/CalculatorApp.hpp"

#include "infrastructure/ComponentFactory.hpp"
#include "runner/Runner.hpp"
#include "core/Exceptions.hpp"

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

        runner::Runner runner(std::move(components.parser), std::move(components.checker),
                              std::move(components.calculator), components.printer);

        runner.run(argc, argv);
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
        catch (const std::filesystem::filesystem_error&)
        {
            return sysConfigPath;
        }
    }

    throw exceptions::ConfigException("Configuration file not found at: " + sysConfigPath);
}

} // namespace app_calculator
