#pragma once

#include "core/IDbAccessor.hpp"
#include "core/IRepository.hpp"
#include "database/DbResult.hpp"
#include "models/Calculation.hpp"

namespace app_calculator::database
{

class HistoryRepository final : public core::IRepository<models::Calculation>
{
  public:
    HistoryRepository(std::shared_ptr<core::IDbAccessor<database::DbResult>> dbAccessor);

    void add(const models::Calculation &item) override;
    std::vector<models::Calculation> getAll() const override;
    std::optional<int64_t> findResult(int64_t operandA, std::optional<int64_t> operandB,
                                      std::string_view operation) const override;

  private:
    std::shared_ptr<core::IDbAccessor<database::DbResult>> _dbAccessor;
};

} // namespace app_calculator::database
