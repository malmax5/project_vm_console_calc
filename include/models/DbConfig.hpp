#pragma once

#include <string>

#include <nlohmann/json_fwd.hpp>

namespace app_calculator::models
{

struct DbConfig
{
  public:
    static constexpr int defaultPostgresPort = 5432;
    static constexpr int defaultPoolSize = 10;

    std::string host;
    int port{defaultPostgresPort};
    std::string dbname;
    std::string user;
    std::string password;

    int poolSize{defaultPoolSize};

    std::string connectionString() const
    {
        return "host=" + host + " port=" + std::to_string(port) + " dbname=" + dbname +
               " user=" + user + " password=" + password;
    }
};

// NOLINTNEXTLINE(readability-identifier-naming)
void to_json(nlohmann::json &jsonData, const DbConfig &dbConfig);

// NOLINTNEXTLINE(readability-identifier-naming)
void from_json(const nlohmann::json &jsonData, DbConfig &dbConfig);

} // namespace app_calculator::models
