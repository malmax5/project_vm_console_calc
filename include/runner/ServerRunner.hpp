#pragma once

#include "core/IRunner.hpp"

#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

namespace grpc
{
class Server;
class Service;
} // namespace grpc

namespace app_calculator::runner
{

class ServerRunner final : public core::IRunner
{
  public:
    ServerRunner(std::shared_ptr<::grpc::Service> service);
    ~ServerRunner() override;

    ServerRunner(const ServerRunner &) = delete;
    ServerRunner &operator=(const ServerRunner &) = delete;
    ServerRunner(ServerRunner &&) noexcept = default;
    ServerRunner &operator=(ServerRunner &&) noexcept = default;

    void run() override;
    void shutdown();

  private:
    std::shared_ptr<::grpc::Service> _service;
    std::unique_ptr<::grpc::Server> _server;

    std::thread signalThread;
    std::atomic<bool> stopRequested{false};
    std::mutex serverMutex;
};

} // namespace app_calculator::runner
