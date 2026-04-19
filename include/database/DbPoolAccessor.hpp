#pragma once

#include "core/IDbAccessor.hpp"
#include "core/IDbConnection.hpp"
#include "infrastructure/ConnectionPool.hpp"

#include <memory>

namespace app_calculator::database
{

template <typename TConnection, typename TResult>
class DbPoolAccessor : public core::IDbAccessor<TResult>
{
public:
    explicit DbPoolAccessor(std::shared_ptr<infrastructure::ConnectionPool<TConnection>> connectionPool);

    ~DbPoolAccessor() override = default;

    DbPoolAccessor(const DbPoolAccessor &) = delete;
    DbPoolAccessor &operator=(const DbPoolAccessor &) = delete;
    DbPoolAccessor(DbPoolAccessor &&) noexcept = default;
    DbPoolAccessor &operator=(DbPoolAccessor &&) noexcept = default;

    TResult execute(const std::string &query) override;
    TResult executeParams(const std::string &query, const std::vector<const char *> &params) override;

private:
    std::shared_ptr<infrastructure::ConnectionPool<TConnection>> _connectionPool;
};

} // namespace app_calculator::database

namespace app_calculator::database
{

template <typename TConnection, typename TResult>
DbPoolAccessor<TConnection, TResult>::DbPoolAccessor(std::shared_ptr<infrastructure::ConnectionPool<TConnection>> connectionPool)
    : _connectionPool(std::move(connectionPool))
{
}

template <typename TConnection, typename TResult>
TResult DbPoolAccessor<TConnection, TResult>::execute(const std::string &query)
{
    auto connection = _connectionPool->acquire();
    return connection->execute(query);
}

template <typename TConnection, typename TResult>
TResult DbPoolAccessor<TConnection, TResult>::executeParams(const std::string &query, const std::vector<const char *> &params)
{
    auto connection = _connectionPool->acquire();
    return connection->executeParams(query, params);
}

} // namespace app_calculator::database
