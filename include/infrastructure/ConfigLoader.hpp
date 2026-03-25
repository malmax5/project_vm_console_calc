#pragma once

#include "core/Exceptions.hpp"

#include <fstream>
#include <string>

namespace app_calculator::infrastructure
{

class ConfigLoader
{
  public:
    template <typename T> static T loadFromFile(const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            throw exceptions::ConfigException("Failed to open config: " + path);
        }

        return parseInternal<T>(file);
    }

  private:
    template <typename T> static T parseInternal(std::ifstream &file);
};

} // namespace app_calculator::infrastructure
