#pragma once

#include "core/IRunner.hpp"
#include "network/CalculatorServiceImpl.hpp"

#include <memory>

namespace grpc
{
class Server;
}

namespace app_calculator::runner
{

class ServerRunner final : public core::IRunner
{
  public:
    ServerRunner(std::shared_ptr<network::CalculatorServiceImpl> service);
    ~ServerRunner() override;

    ServerRunner(const ServerRunner &) = delete;
    ServerRunner &operator=(const ServerRunner &) = delete;
    ServerRunner(ServerRunner &&) noexcept = default;
    ServerRunner &operator=(ServerRunner &&) noexcept = default;

    void run() override;
    void shutdown();

  private:
    std::shared_ptr<network::CalculatorServiceImpl> _service;
    std::unique_ptr<::grpc::Server> _server;
};

} // namespace app_calculator::runner
