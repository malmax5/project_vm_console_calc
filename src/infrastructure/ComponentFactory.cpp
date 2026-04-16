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
#include "parser/JsonParser.hpp"
#include "printer/Printer.hpp"
#include "runner/ConsoleRunner.hpp"
#include "runner/ServerRunner.hpp"
#include "network/CalculatorServiceImpl.hpp"

namespace app_calculator::infrastructure
{

AppComponents ComponentFactory::createProductionComponents(const std::string &configPath)
{
    models::DbConfig config =
        infrastructure::ConfigLoader::loadFromFile<models::DbConfig>(configPath);

    auto dbConnection = std::make_shared<database::PostgresConnection>(config.connectionString());
    auto historyRepository = std::make_unique<database::HistoryRepository>(dbConnection);

    auto baseCalculator = std::make_unique<calculator::Calculator>();

    AppComponents components;
    components.parser = std::make_unique<parser::JsonParser>();
    components.checker = std::make_unique<checker::Checker>();
    components.printer = std::make_shared<printer::Printer>(logger::Logger::instance());

    auto cachedRepository = std::make_shared<database::CachedHistoryRepository>(
        std::move(historyRepository), components.printer);
    components.calculator =
        std::make_unique<calculator::CachedCalculator>(std::move(baseCalculator), cachedRepository);

    return components;
}

std::unique_ptr<core::IRunner> ComponentFactory::createConsoleRunner(const std::string &configPath,
                                                                     std::string &inputJson)
{
    auto components = createProductionComponents(configPath);

    return std::make_unique<runner::ConsoleRunner>(
        std::move(components.parser), std::move(components.checker),
        std::move(components.calculator), components.printer, inputJson);
}

std::unique_ptr<core::IRunner> ComponentFactory::createServerRunner(const std::string &configPath)
{
    AppComponents components = createProductionComponents(configPath);

    auto service = std::make_shared<network::CalculatorServiceImpl>(
        std::move(components.calculator), std::move(components.checker), components.printer);

    return std::make_unique<runner::ServerRunner>(service);
}

} // namespace app_calculator::infrastructure
