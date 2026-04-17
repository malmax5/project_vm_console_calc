#include "runner/ServerRunner.hpp"

#include "core/Constants.hpp"
#include "core/Exceptions.hpp"

#include <atomic>
#include <cerrno>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <pthread.h>
#include <stdexcept>
#include <thread>

namespace app_calculator::runner
{

ServerRunner::ServerRunner(std::shared_ptr<::grpc::Service> service,
                           std::shared_ptr<core::IPrinter> printer)
    : _service(std::move(service)), _printer(printer)
{
}

ServerRunner::~ServerRunner()
{
    shutdown();
}

void ServerRunner::run()
{
    try
    {
        setupSignalMask();
        startGrpcServer();
        startSignalThread();

        if (_server)
        {
            _printer->printInfo("gRPC server started on " + serverAddress);
            _server->Wait();
        }

        stopRequested.store(true);
        if (signalThread.joinable())
        {
            signalThread.join();
        }
    }
    catch (const exceptions::NetworkException &e)
    {
        if (_printer)
        {
            _printer->printError(e.what());
        }
        throw;
    }
    catch (const std::exception &e)
    {
        if (_printer)
        {
            _printer->printError(std::string("Unexpected error: ") + e.what());
        }
        throw exceptions::NetworkException(std::string("ServerRunner encountered an error: ") +
                                           e.what());
    }
    catch (...)
    {
        if (_printer)
        {
            _printer->printError("An unknown error occurred in ServerRunner.");
        }
        throw exceptions::NetworkException("ServerRunner encountered an unknown error.");
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
        if (_printer)
        {
            _printer->printInfo("Shutdown signal received.");
        }

        std::lock_guard<std::mutex> lock(serverMutex);
        if (_server)
        {
            _server->Shutdown();
        }
    }
}

void ServerRunner::setupSignalMask()
{
    sigemptyset(&signalSet);
    sigaddset(&signalSet, SIGINT);
    sigaddset(&signalSet, SIGTERM);

    int maskResult = pthread_sigmask(SIG_BLOCK, &signalSet, nullptr);
    if (maskResult != 0)
    {
        throw exceptions::NetworkException("pthread_sigmask failed: " +
                                           std::string(std::strerror(maskResult)));
    }
}

void ServerRunner::startGrpcServer()
{
    serverAddress = core::defaultServerAddress;
    ::grpc::ServerBuilder builder;

    ::grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    builder.AddListeningPort(serverAddress, ::grpc::InsecureServerCredentials());
    builder.RegisterService(_service.get());

    _server = builder.BuildAndStart();
    if (!_server)
    {
        throw exceptions::GrpcException("Failed to start gRPC server");
    }
}

void ServerRunner::startSignalThread()
{
    signalThread = std::thread(
        [this]() mutable
        {
            timespec timeout{0, core::signalWaitNanoseconds};
            while (!stopRequested.load())
            {
                int signal = sigtimedwait(&signalSet, nullptr, &timeout);
                if (signal == -1)
                {
                    if (errno == EAGAIN || errno == EINTR)
                    {
                        continue;
                    }

                    shutdown();
                    break;
                }

                if (signal == -1 && errno != EAGAIN && errno != EINTR)
                {
                    if (_printer)
                    {
                        _printer->printError(std::string("sigtimedwait failed: ") +
                                             std::strerror(errno));
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
}

} // namespace app_calculator::runner
