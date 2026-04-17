#include "application/CalculatorApp.hpp"

#include "application/CLIOptions.hpp"
#include "infrastructure/ComponentFactory.hpp"
#include "infrastructure/RunnerFactory.hpp"
#include "core/Exceptions.hpp"

#include <filesystem>

namespace app_calculator
{

void CalculatorApp::run(int argc, char **argv)
{
    try
    {
        CLIOptions options = CLIOptions::parse(argc, argv);
        
        if (options.configPath.empty())
        {
            std::string configPath = getResourcePath(argv[0]);
            options.configPath = configPath;
        }

        {
            auto components = infrastructure::ComponentFactory::createProductionContext(configPath);
            _printer = components.printer;
        }

        _printer->printInfo("Application started");

        std::unique_ptr<core::IRunner> runner;
        switch (options.mode)
        {
        case AppMode::Server:
            _printer->printInfo("Mode: SERVER");
            {
                infrastructure::ServerRunnerDeps deps = infrastructure::ComponentFactory::createServerRunnerComponents(options);
                runner = infrastructure::RunnerFactory::createServerRunner(deps);
            }
            break;
        case AppMode::Console:
            _printer->printInfo("Mode: CONSOLE");
            {
                infrastructure::ConsoleRunnerDeps deps = infrastructure::ComponentFactory::createConsoleRunnerComponents(options);
                runner = infrastructure::RunnerFactory::createConsoleRunner(deps);
            }
            break;
        case AppMode::Client:
            _printer->printInfo("Mode: CLIENT");
            {
                infrastructure::ClientRunnerDeps deps = infrastructure::ComponentFactory::createClientRunnerComponents(options);
                runner = infrastructure::RunnerFactory::createClientRunner(deps);
            }
            break;
        default:
            throw exceptions::ConfigException("Invalid mode specified. Use --server, --console, or --client.");
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
