#include "application/CalculatorApp.hpp"

#include "application/CLIOptions.hpp"
#include "core/Exceptions.hpp"
#include "infrastructure/ComponentFactory.hpp"
#include "infrastructure/RunnerFactory.hpp"

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
            auto components = infrastructure::ComponentFactory::createApplicationContext();
            _printer = components.printer;
        }

        _printer->printInfo("Application started");

        std::unique_ptr<core::IRunner> runner;
        switch (options.mode)
        {
        case AppMode::server:
            _printer->printInfo("Mode: SERVER");
            {
                infrastructure::ServerRunnerDeps deps =
                    infrastructure::ComponentFactory::createServerRunnerComponents(options);
                runner = infrastructure::RunnerFactory::createServerRunner(deps);
            }
            break;
        case AppMode::console:
            _printer->printInfo("Mode: CONSOLE");
            {
                infrastructure::ConsoleRunnerDeps deps =
                    infrastructure::ComponentFactory::createConsoleRunnerComponents(options);
                runner = infrastructure::RunnerFactory::createConsoleRunner(deps);
            }
            break;
        case AppMode::client:
            _printer->printInfo("Mode: CLIENT");
            {
                infrastructure::ClientRunnerDeps deps =
                    infrastructure::ComponentFactory::createClientRunnerComponents(options);
                runner = infrastructure::RunnerFactory::createClientRunner(deps);
            }
            break;
        default:
            throw exceptions::ConfigException(
                "Invalid mode specified. Use --server, --console, or --client.");
        }

        runner->run();
    }
    catch (const exceptions::NetworkException &e)
    {
        if (_printer)
        {
            _printer->printError("Network error: " + std::string(e.what()));
        }

        return;
    }
    catch (const exceptions::AppException &e)
    {
        if (_printer)
        {
            _printer->printError("Application error: " + std::string(e.what()));
        }

        return;
    }
    catch (const std::exception &e)
    {
        if (_printer)
        {
            _printer->printError("Initialization failed: " + std::string(e.what()));
        }

        return;
    }
    catch (...)
    {
        if (_printer)
        {
            _printer->printError("Initialization failed: Unknown error");
        }

        return;
    }
}

std::string CalculatorApp::getResourcePath(const char *executablePath)
{
    const std::string sysConfigPath = core::configPath;
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
