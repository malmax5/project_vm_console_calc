#pragma once

#include "core/IRepository.hpp"
#include "database/DbResult.hpp"
#include "models/Calculation.hpp"

#include <memory>
#include <unordered_map>

namespace app_calculator::database
{

class CachedHistoryRepository : public core::IRepository<models::Calculation>
{
  public:
    explicit CachedHistoryRepository(
        std::unique_ptr<core::IRepository<models::Calculation>> repository);

    void add(const models::Calculation &item) override;
    std::vector<models::Calculation> getAll() const override;
    std::optional<int64_t> findResult(int64_t operandA, std::optional<int64_t> operandB,
                                      std::string_view operation) const override;

  private:
    void warmUpCache();

    std::unique_ptr<core::IRepository<models::Calculation>> _repository;

    mutable std::unordered_map<std::string, int64_t> _cache;
};

} // namespace app_calculator::database
