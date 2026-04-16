#include "runner/ServerRunner.hpp"

#include <grpcpp/grpcpp.h>

namespace app_calculator::runner
{

ServerRunner::ServerRunner(std::shared_ptr<network::CalculatorServiceImpl> service)
    : _service(std::move(service))
{
}

ServerRunner::~ServerRunner()
{
    shutdown();
}

void ServerRunner::run()
{
    std::string serverAddress("0.0.0.0:50051");

    ::grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress, ::grpc::InsecureServerCredentials());
    builder.RegisterService(_service.get());

    _server = builder.BuildAndStart();
    std::cout << "Server is listening on " << serverAddress << std::endl;

    _server->Wait();
}

void ServerRunner::shutdown()
{
    if (_server)
    {
        _server->Shutdown();
        _server->Wait();
    }
}

} // namespace app_calculator::runner
