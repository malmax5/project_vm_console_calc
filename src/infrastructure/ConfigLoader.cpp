#include "infrastructure/ConfigLoader.hpp"

#include "models/DbConfig.hpp"
#include <nlohmann/json.hpp>

namespace app_calculator::infrastructure
{

template <typename T> T ConfigLoader::parseInternal(std::ifstream &file)
{
    try
    {
        nlohmann::json jsonData;
        file >> jsonData;

        return jsonData.get<T>();
    }
    catch (const nlohmann::json::exception &e)
    {
        throw exceptions::ConfigException(std::string("JSON parsing error: ") + e.what());
    }
}

template models::DbConfig ConfigLoader::parseInternal<models::DbConfig>(std::ifstream &);

} // namespace app_calculator::infrastructure
