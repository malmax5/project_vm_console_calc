#pragma once

#include <string>

namespace app_calculator::models
{

struct OperationInfo
{
  public:
    std::string name;
    size_t expectedArgs;

    bool operator<(const OperationInfo& other) const
    {
        return name < other.name;
    }
};

} // namespace app_calculator::models
