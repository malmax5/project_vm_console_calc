#pragma once

#include "core/ICalculator.hpp"
#include "core/IRepository.hpp"
#include "models/Calculation.hpp"
#include "models/CalculationTask.hpp"

#include <memory>

namespace app_calculator::calculator
{

class CachedCalculator final : public core::ICalculator
{
  public:
    CachedCalculator(std::unique_ptr<core::ICalculator> calculator,
                     std::shared_ptr<core::IRepository<models::Calculation>> repository);
    ~CachedCalculator() override = default;

    CachedCalculator(const CachedCalculator &) = delete;
    CachedCalculator &operator=(CachedCalculator &) = delete;
    CachedCalculator(CachedCalculator &&) noexcept = default;
    CachedCalculator &operator=(CachedCalculator &&) noexcept = default;

    long long calculate(const models::CalculationTask &task) override;

  private:
    std::unique_ptr<core::ICalculator> _calculator;
    std::shared_ptr<core::IRepository<models::Calculation>> _repository;
};

} // namespace app_calculator::calculator
