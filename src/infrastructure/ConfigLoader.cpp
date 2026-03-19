#include "infrastructure/ConfigLoader.hpp"

#include "models/DbConfig.hpp"
#include <nlohmann/json.hpp>

namespace app_calculator::infrastructure
{

template <typename T>
T ConfigLoader::parseInternal(std::ifstream& file)
{
    nlohmann::json jsonData;
    file >> jsonData;

    return jsonData.get<T>(); 
}

template models::DbConfig ConfigLoader::parseInternal<models::DbConfig>(std::ifstream&);

} // namespace app_calculator::infrastructure
