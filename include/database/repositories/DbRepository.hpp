#pragma once

#include "core/IDbConnection.hpp"
#include <memory>

namespace app_calculator::database
{

template <typename TResult> class DbRepository
{
  public:
    DbRepository(std::shared_ptr<core::IDbConnection<TResult>> dbConnection)
        : _dbConnection(std::move(dbConnection))
    {
    }
    virtual ~DbRepository() = default;

    DbRepository(const DbRepository &) = delete;
    DbRepository &operator=(const DbRepository &) = delete;
    DbRepository(DbRepository &&) noexcept = default;
    DbRepository &operator=(DbRepository &&) noexcept = default;

  protected:
    auto &getDbConnection() const
    {
        return *_dbConnection;
    }

  private:
    std::shared_ptr<core::IDbConnection<TResult>> _dbConnection;
};

} // namespace app_calculator::database
