#pragma once

#include "core/IPrinter.hpp"
#include "core/IRunner.hpp"

#include <atomic>
#include <csignal>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

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
    ServerRunner(std::shared_ptr<::grpc::Service> service, std::shared_ptr<core::IPrinter> printer);
    ~ServerRunner() override;

    ServerRunner(const ServerRunner &) = delete;
    ServerRunner &operator=(const ServerRunner &) = delete;
    ServerRunner(ServerRunner &&) noexcept = default;
    ServerRunner &operator=(ServerRunner &&) noexcept = default;

    void run() override;
    void shutdown();

  private:
    void setupSignalMask();
    void startGrpcServer();
    void startSignalThread();

    std::shared_ptr<::grpc::Service> _service;
    std::unique_ptr<::grpc::Server> _server;
    std::shared_ptr<core::IPrinter> _printer;

    std::thread signalThread;
    std::atomic<bool> stopRequested{false};
    std::mutex serverMutex;

    sigset_t signalSet{};
    std::string serverAddress;
};

} // namespace app_calculator::runner
