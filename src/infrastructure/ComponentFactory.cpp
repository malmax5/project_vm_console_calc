#include "infrastructure/ComponentFactory.hpp"

#include "calculator/CachedCalculator.hpp"
#include "calculator/Calculator.hpp"
#include "checker/Checker.hpp"
#include "database/PostgresConnection.hpp"
#include "database/repositories/CachedHistoryRepository.hpp"
#include "database/repositories/HistoryRepository.hpp"
#include "infrastructure/ConfigLoader.hpp"
#include "logger/Logger.hpp"
#include "models/DbConfig.hpp"
#include "network/CalculatorServiceImpl.hpp"
#include "parser/JsonParser.hpp"
#include "printer/Printer.hpp"

#include <grpcpp/grpcpp.h>

namespace app_calculator::infrastructure
{

AppContext ComponentFactory::createApplicationContext()
{
    AppContext context;

    context.printer = std::make_shared<printer::Printer>(logger::Logger::instance());

    return context;
}

ConsoleRunnerDeps ComponentFactory::createConsoleRunnerComponents(const CLIOptions &options)
{
    ConsoleRunnerDeps deps;

    models::DbConfig config =
        infrastructure::ConfigLoader::loadFromFile<models::DbConfig>(options.configPath);

    auto dbConnection = std::make_shared<database::PostgresConnection>(config.connectionString());
    auto historyRepository = std::make_unique<database::HistoryRepository>(dbConnection);

    auto baseCalculator = std::make_unique<calculator::Calculator>();

    deps.parser = std::make_unique<parser::JsonParser>();
    deps.checker = std::make_unique<checker::Checker>();
    deps.printer = std::make_shared<printer::Printer>(logger::Logger::instance());
    auto cachedRepository = std::make_shared<database::CachedHistoryRepository>(
        std::move(historyRepository), deps.printer);
    deps.calculator =
        std::make_unique<calculator::CachedCalculator>(std::move(baseCalculator), cachedRepository);
    deps.inputJson = options.inputJson;

    return deps;
}

ServerRunnerDeps ComponentFactory::createServerRunnerComponents(const CLIOptions &options)
{
    ServerRunnerDeps deps;

    models::DbConfig config =
        infrastructure::ConfigLoader::loadFromFile<models::DbConfig>(options.configPath);

    auto dbConnection = std::make_shared<database::PostgresConnection>(config.connectionString());
    auto historyRepository = std::make_unique<database::HistoryRepository>(dbConnection);

    auto baseCalculator = std::make_unique<calculator::Calculator>();

    deps.printer = std::make_shared<printer::Printer>(logger::Logger::instance());
    auto cachedRepository = std::make_shared<database::CachedHistoryRepository>(
        std::move(historyRepository), deps.printer);
    deps.calculator =
        std::make_unique<calculator::CachedCalculator>(std::move(baseCalculator), cachedRepository);
    deps.checker = std::make_unique<checker::Checker>();

    return deps;
}

ClientRunnerDeps ComponentFactory::createClientRunnerComponents(const CLIOptions &options)
{
    ClientRunnerDeps deps;

    deps.printer = std::make_shared<printer::Printer>(logger::Logger::instance());
    deps.parser = std::make_unique<parser::JsonParser>();
    deps.inputJson = options.inputJson;
    deps.serverAddress = options.serverAddress;
    deps.timeoutMs = options.timeoutMs;

    return deps;
}

} // namespace app_calculator::infrastructure
