#pragma once

#include "calculator.grpc.pb.h"
#include "core/IRunner.hpp"
#include "infrastructure/RunnerDeps.hpp"

#include <memory>

namespace grpc
{

class Channel;

}

namespace app_calculator::runner
{

class ClientRunner final : public core::IRunner
{
  public:
    explicit ClientRunner(std::shared_ptr<::grpc::Channel> channel, const infrastructure::ClientRunnerDeps &deps);
    ~ClientRunner() override;

    ClientRunner(const ClientRunner &) = delete;
    ClientRunner &operator=(const ClientRunner &) = delete;
    ClientRunner(ClientRunner &&) noexcept = default;
    ClientRunner &operator=(ClientRunner &&) noexcept = default;

    void run() override;

  private:
    std::unique_ptr<::app_calculator::grpc::CalculatorService::Stub> _stub;
    std::shared_ptr<core::IPrinter> _printer;
    int _timeoutMs;
    models::CalculationTask _task;
};

} // namespace app_calculator::runner
