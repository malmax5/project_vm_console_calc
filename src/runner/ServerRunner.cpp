#include "runner/ServerRunner.hpp"

#include <csignal>
#include <thread>
#include <atomic>
#include <iostream>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

namespace app_calculator::runner
{

namespace
{

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::atomic<ServerRunner*> gServerInstance{nullptr};

} // namespace

void handleSignal(int signal)
{
    if (gServerInstance.load() != nullptr)
    {
        std::cout << "\n[Signal Handler] Received signal " << signal << ", shutting down server...\n";
        gServerInstance.load()->shutdown();
    }
}

ServerRunner::ServerRunner(std::shared_ptr<::grpc::Service> service)
    : _service(std::move(service))
{
    gServerInstance.store(this);
}

ServerRunner::~ServerRunner()
{
    shutdown();
    gServerInstance.store(nullptr);
}

void ServerRunner::run()
{
    std::string serverAddress("0.0.0.0:50051");
    ::grpc::ServerBuilder builder;

    ::grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    builder.AddListeningPort(serverAddress, ::grpc::InsecureServerCredentials());
    builder.RegisterService(_service.get());

    _server = builder.BuildAndStart();
    if (!_server)
    {
        throw std::runtime_error("Failed to start gRPC server");
    }
    std::cout << "Server is listening on " << serverAddress << std::endl;

    std::signal(SIGINT, handleSignal);
    std::signal(SIGTERM, handleSignal);

    _server->Wait();

    std::cout << "Server successfully stopped." << std::endl;
}

void ServerRunner::shutdown()
{
    if (_server)
    {
        std::thread([this]() {
            _server->Shutdown();
        }).detach();
    }
}

} // namespace app_calculator::runner
