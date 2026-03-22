#include "database/repositories/CachedHistoryRepository.hpp"

#include "models/Operations.hpp"
#include "utils/OperationUtils.hpp"

#include <stdexcept>

namespace app_calculator::database
{

CachedHistoryRepository::CachedHistoryRepository(
    std::unique_ptr<core::IRepository<models::Calculation>> repository)
    : _repository(std::move(repository))
{
    warmUpCache();
}

void CachedHistoryRepository::add(const models::Calculation &item)
{
    _repository->add(item);

    if (item.status == models::OperationStatus::success && item.result.has_value())
    {
        std::string key =
            utils::operations::makeOperationKey(item.operandA, item.operandB, item.operation);
        _cache[key] = *item.result;
    }
}

std::vector<models::Calculation> CachedHistoryRepository::getAll() const
{
    return _repository->getAll();
}

std::optional<int64_t> CachedHistoryRepository::findResult(int64_t operandA,
                                                           std::optional<int64_t> operandB,
                                                           std::string_view operation) const
{
    std::string key = utils::operations::makeOperationKey(operandA, operandB, operation);

    const auto &itKey = _cache.find(key);
    if (itKey != _cache.end())
    {
        return itKey->second;
    }

    auto dbResult = _repository->findResult(operandA, operandB, operation);
    if (dbResult.has_value())
    {
        _cache[key] = *dbResult;
    }

    return dbResult;
}

void CachedHistoryRepository::warmUpCache()
{
    auto const &allHistroy = _repository->getAll();

    for (const auto &item : allHistroy)
    {
        if (item.status == models::OperationStatus::success && item.result.has_value())
        {
            try
            {
                std::string key = utils::operations::makeOperationKey(item.operandA, item.operandB,
                                                                      item.operation);
                _cache[key] = *item.result;
            }
            catch (const std::exception &e)
            {
                continue;
            }
        }
    }
}

} // namespace app_calculator::database
