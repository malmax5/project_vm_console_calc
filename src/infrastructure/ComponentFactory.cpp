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

AppContext ComponentFactory::createProductionContext(const std::string &configPath)
{
    models::DbConfig config =
        infrastructure::ConfigLoader::loadFromFile<models::DbConfig>(configPath);

    auto dbConnection = std::make_shared<database::PostgresConnection>(config.connectionString());
    auto historyRepository = std::make_unique<database::HistoryRepository>(dbConnection);

    auto baseCalculator = std::make_unique<calculator::Calculator>();

    AppContext context;
    context.parser = std::make_unique<parser::JsonParser>();
    context.checker = std::make_unique<checker::Checker>();
    context.printer = std::make_shared<printer::Printer>(logger::Logger::instance());

    auto cachedRepository = std::make_shared<database::CachedHistoryRepository>(
        std::move(historyRepository), context.printer);
    context.calculator =
        std::make_unique<calculator::CachedCalculator>(std::move(baseCalculator), cachedRepository);

    return context;
}

} // namespace app_calculator::infrastructure
