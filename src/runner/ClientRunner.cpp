#include "runner/ClientRunner.hpp"

#include <grpcpp/channel.h>
#include <iostream>
#include <chrono>

namespace app_calculator::runner
{

ClientRunner::ClientRunner(std::shared_ptr<::grpc::Channel> channel, const infrastructure::ClientRunnerDeps &deps)
    : _stub(::app_calculator::grpc::CalculatorService::NewStub(channel))
    , _printer(deps.printer)
    , _timeoutMs(deps.timeoutMs)
    , _task(deps.task)
{
}

ClientRunner::~ClientRunner()
{
}

void ClientRunner::run()
{
    ::app_calculator::grpc::CalculationRequest request;
    request.set_operation(_task.operation);
    for (const auto &operand : _task.operands)
    {
        request.add_operands(operand);
    }

    ::app_calculator::grpc::CalculationResponse response;
    ::grpc::ClientContext context;
    auto deadline = std::chrono::system_clock::now() + std::chrono::milliseconds(_timeoutMs);
    context.set_deadline(deadline);

    _printer->printInfo("[Client] Connecting to server...");
    ::grpc::Status status = _stub->Calculate(&context, request, &response);

    if (status.ok())
    {
        _printer->printInfo("[Client] Result: " + std::to_string(response.result()));
        _printer->printInfo("[Client] Status: " + response.status());
    }
    else
    {
        _printer->printError("[Client] RPC failed: " + "code=" + std::to_string(static_cast<int>(status.error_code())) + ", name=" + ::grpc::StatusCodeToString(status.error_code()) + ", message=" + status.error_message());
    }
}

} // namespace app_calculator::runner
