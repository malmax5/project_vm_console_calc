#include "models/DbConfig.hpp"

#include <nlohmann/json.hpp>

namespace app_calculator::models
{

void to_json(nlohmann::json &jsonData, const DbConfig &dbConfig)
{
    jsonData = nlohmann::json{{"host", dbConfig.host},
                              {"port", dbConfig.port},
                              {"dbname", dbConfig.dbname},
                              {"user", dbConfig.user},
                              {"password", dbConfig.password}};
}

void from_json(const nlohmann::json &jsonData, DbConfig &dbConfig)
{
    if (jsonData.contains("database")) 
    {
        const auto& jsonDataAtDb = jsonData.at("database");
        
        jsonDataAtDb.at("host").get_to(dbConfig.host);
        jsonDataAtDb.at("port").get_to(dbConfig.port);
        jsonDataAtDb.at("dbname").get_to(dbConfig.dbname);
        jsonDataAtDb.at("user").get_to(dbConfig.user);
        jsonDataAtDb.at("password").get_to(dbConfig.password);
    }
}

} // namespace app_calculator::models
