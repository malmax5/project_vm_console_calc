#pragma once

#include "core/IDbAccessor.hpp"
#include "core/IDbConnection.hpp"

#include <memory>

namespace app_calculator::database
{

template <typename TResult>
class DbSingleAccessor : public core::IDbAccessor<TResult>
{
public:
    explicit DbSingleAccessor(std::shared_ptr<core::IDbConnection<TResult>> dbConnection);

    ~DbSingleAccessor() override = default;

    DbSingleAccessor(const DbSingleAccessor &) = delete;
    DbSingleAccessor &operator=(const DbSingleAccessor &) = delete;
    DbSingleAccessor(DbSingleAccessor &&) noexcept = default;
    DbSingleAccessor &operator=(DbSingleAccessor &&) noexcept = default;

    TResult execute(const std::string &query) override;
    TResult executeParams(const std::string &query, const std::vector<const char *> &params) override;

private:
    std::shared_ptr<core::IDbConnection<TResult>> _dbConnection;
};

} // namespace app_calculator::database

namespace app_calculator::database
{

template <typename TResult>
DbSingleAccessor<TResult>::DbSingleAccessor(std::shared_ptr<core::IDbConnection<TResult>> dbConnection)
    :_dbConnection(std::move(dbConnection))
{
}

template <typename TResult>
TResult DbSingleAccessor<TResult>::execute(const std::string &query)
{
    return _dbConnection->execute(query);
}

template <typename TResult>
TResult DbSingleAccessor<TResult>::executeParams(const std::string &query, const std::vector<const char *> &params)
{
    return _dbConnection->executeParams(query, params);
}

} // namespace app_calculator::database
