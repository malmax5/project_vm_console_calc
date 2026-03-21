#pragma once

#include <string_view>

namespace app_calculator::models
{

struct OperationInfo
{
  public:
    std::string_view name;
    size_t expectedArgs;
    bool isCommutative;

    bool operator<(const OperationInfo &other) const
    {
        return name < other.name;
    }
};

} // namespace app_calculator::models
