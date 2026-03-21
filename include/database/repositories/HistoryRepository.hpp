#pragma once

#include "core/IRepository.hpp"
#include "database/DbResult.hpp"
#include "database/repositories/DbRepository.hpp"
#include "models/Calculation.hpp"

namespace app_calculator::database
{

class HistoryRepository final : public core::IRepository<models::Calculation>,
                                public DbRepository<DbResult>
{
  public:
    using DbRepository<DbResult>::DbRepository;

    void add(const models::Calculation &item) override;
    std::vector<models::Calculation> getAll() const override;
    std::optional<int64_t> findResult(int64_t operandA, std::optional<int64_t> operandB,
                                      std::string_view operation) const override;
};

} // namespace app_calculator::database
