#include "database/repositories/DbRepository.hpp"

namespace app_calculator::database
{

template <typename TResult>
DbRepository<TResult>::DbRepository(std::shared_ptr<core::IDbConnection<TResult>> dbConnection)
    : _dbConnection(std::move(dbConnection))
{
}

} // namespace app_calculator::database