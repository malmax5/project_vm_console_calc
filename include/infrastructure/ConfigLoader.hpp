#pragma once

#include <string>
#include <fstream>

namespace app_calculator::infrastructure
{

class ConfigLoader
{
public:
    template <typename T>
    static T loadFromFile(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open config: " + path);
        }

        return parseInternal<T>(file);
    }

private:
    template <typename T>
    static T parseInternal(std::ifstream& file);
};

} // namespace app_calculator::infrastructure
