#include "runner/ServerRunner.hpp"

#include "core/Constants.hpp"

#include <atomic>
#include <cerrno>
#include <csignal>
#include <cstring>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <pthread.h>
#include <stdexcept>
#include <thread>

namespace app_calculator::runner
{

ServerRunner::ServerRunner(std::shared_ptr<::grpc::Service> service) : _service(std::move(service))
{
}

ServerRunner::~ServerRunner()
{
    shutdown();
}

void ServerRunner::run()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    int maskResult = pthread_sigmask(SIG_BLOCK, &set, nullptr);
    if (maskResult != 0)
    {
        throw std::runtime_error("pthread_sigmask failed: " +
                                 std::string(std::strerror(maskResult)));
    }

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

    signalThread = std::thread(
        [this, set]() mutable
        {
            timespec timeout{0, core::signalWaitNanoseconds};
            while (!stopRequested.load())
            {
                int signal = sigtimedwait(&set, nullptr, &timeout);
                if (signal == -1)
                {
                    if (errno == EAGAIN || errno == EINTR)
                    {
                        continue;
                    }

                    shutdown();
                    break;
                }

                if (signal == SIGINT || signal == SIGTERM)
                {
                    shutdown();
                    break;
                }
            }
        });

    _server->Wait();

    stopRequested.store(true);
    if (signalThread.joinable())
    {
        signalThread.join();
    }
}

void ServerRunner::shutdown()
{
    bool expected = false;
    if (!stopRequested.compare_exchange_strong(expected, true))
    {
        return;
    }

    {
        std::lock_guard<std::mutex> lock(serverMutex);
        if (_server)
        {
            _server->Shutdown();
        }
    }
}

} // namespace app_calculator::runner
