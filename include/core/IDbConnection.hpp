#pragma once

#include <string>

namespace app_calculator::core
{

template <typename TResult> class IDbConnection
{
  public:
    IDbConnection() = default;
    virtual ~IDbConnection() = default;

    IDbConnection(const IDbConnection &) = delete;
    IDbConnection &operator=(const IDbConnection &) = delete;
    IDbConnection(IDbConnection &&) noexcept = default;
    IDbConnection &operator=(IDbConnection &&) noexcept = default;

    virtual TResult execute(const std::string &query) = 0;
    virtual bool isConnected() const = 0;
};

} // namespace app_calculator::core
