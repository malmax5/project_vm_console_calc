#include "runner/ClientRunner.hpp"

#include "models/CalculationTask.hpp"

#include <grpcpp/channel.h>
#include <chrono>

namespace app_calculator::runner
{

ClientRunner::ClientRunner(std::shared_ptr<::grpc::Channel> channel, infrastructure::ClientRunnerDeps &deps)
    : _stub(::app_calculator::grpc::CalculatorService::NewStub(channel))
    , _printer(deps.printer)
    , _parser(std::move(deps.parser))
    , inputJson(deps.inputJson)
    , _timeoutMs(deps.timeoutMs)
{
}

ClientRunner::~ClientRunner()
{
}

void ClientRunner::run()
{
    ::app_calculator::grpc::CalculationRequest request;

    models::CalculationTask task = _parser->parse(inputJson);

    request.set_operation(task.operation);
    for (const auto &operand : task.operands)
    {
        request.add_operands(operand);
    }

    ::app_calculator::grpc::CalculationResponse response;
    ::grpc::ClientContext context;
    if (_timeoutMs > 0)
    {
        auto deadline = std::chrono::system_clock::now() + std::chrono::milliseconds(_timeoutMs);
        context.set_deadline(deadline);
    }

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
