#include "application/CalculatorApp.hpp"

#include "infrastructure/ComponentFactory.hpp"
#include "runner/Runner.hpp"

#include <filesystem>

namespace app_calculator
{

void CalculatorApp::run(int argc, char **argv)
{
    try
    {
        std::string configPath = getResourcePath(argv[0]);

        auto components = infrastructure::ComponentFactory::createProductionComponents(configPath);

        runner::Runner runner(std::move(components.parser), std::move(components.checker),
                              std::move(components.calculator), std::move(components.printer));

        runner.run(argc, argv);
    }
    catch (const std::exception &e)
    {
        throw;
    }
    catch (...)
    {
        throw;
    }
}

std::string CalculatorApp::getResourcePath(const char *executablePath)
{
    std::filesystem::path execPath = std::filesystem::absolute(executablePath);
    std::filesystem::path executableDir = execPath.parent_path();
    std::filesystem::path configPath = executableDir / ".." / "config" / "config.json";

    if (std::filesystem::exists(configPath))
    {
        return std::filesystem::canonical(configPath).string();
    }

    return "config/config.json";
}

} // namespace app_calculator
