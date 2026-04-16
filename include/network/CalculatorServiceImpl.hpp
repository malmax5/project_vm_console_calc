#pragma once

#include "calculator.grpc.pb.h"
#include "core/ICalculator.hpp"
#include "core/IChecker.hpp"
#include "core/IPrinter.hpp"

#include <memory>

namespace app_calculator::network
{

class CalculatorServiceImpl final : public grpc::CalculatorService::Service
{
  public:
    explicit CalculatorServiceImpl(std::unique_ptr<core::ICalculator> calculator,
                                   std::unique_ptr<core::IChecker> checker,
                                   std::shared_ptr<core::IPrinter> printer);
    ~CalculatorServiceImpl() override = default;

    CalculatorServiceImpl(const CalculatorServiceImpl &) = delete;
    CalculatorServiceImpl &operator=(const CalculatorServiceImpl &) = delete;
    CalculatorServiceImpl(CalculatorServiceImpl &&) noexcept = delete;
    CalculatorServiceImpl &operator=(CalculatorServiceImpl &&) noexcept = delete;

    ::grpc::Status Calculate(::grpc::ServerContext *context,
                             const app_calculator::grpc::CalculationRequest *request,
                             app_calculator::grpc::CalculationResponse *response) override;

  private:
    std::unique_ptr<core::ICalculator> _calculator;
    std::unique_ptr<core::IChecker> _checker;
    std::shared_ptr<core::IPrinter> _printer;
};

} // namespace app_calculator::network
