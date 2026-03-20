#pragma once

#include <string>

namespace app_calculator::core
{

template <typename TResult> class IDbConnection
{
  public:
    virtual ~IDbConnection() = default;

    virtual TResult execute(const std::string &query) = 0;
    virtual bool isConnected() const = 0;
};

} // namespace app_calculator::core
