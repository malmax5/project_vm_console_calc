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
    jsonData.at("host").get_to(dbConfig.host);
    jsonData.at("port").get_to(dbConfig.port);
    jsonData.at("dbname").get_to(dbConfig.dbname);
    jsonData.at("user").get_to(dbConfig.user);
    jsonData.at("password").get_to(dbConfig.password);
}

} // namespace app_calculator::models
