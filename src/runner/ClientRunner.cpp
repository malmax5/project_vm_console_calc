#include "runner/ClientRunner.hpp"

#include "core/Exceptions.hpp"
#include "models/CalculationTask.hpp"
#include "utils/ErrorCodeUtils.hpp"
#include "utils/GrpcUtils.hpp"

#include <chrono>
#include <grpcpp/channel.h>

namespace app_calculator::runner
{

ClientRunner::ClientRunner(std::shared_ptr<::grpc::Channel> channel,
                           infrastructure::ClientRunnerDeps &deps)
    : _stub(::app_calculator::grpc::CalculatorService::NewStub(channel)), _printer(deps.printer),
      _parser(std::move(deps.parser)), inputJson(deps.inputJson), _timeoutMs(deps.timeoutMs)
{
}

ClientRunner::~ClientRunner()
{
}

void ClientRunner::run()
{
    try
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
            auto deadline =
                std::chrono::system_clock::now() + std::chrono::milliseconds(_timeoutMs);
            context.set_deadline(deadline);
        }

        _printer->printInfo("[Client] Connecting to server...");

        ::grpc::Status status;
        try
        {
            status = _stub->Calculate(&context, request, &response);

            _printer->printInfo("[Client] Sending request: " + inputJson);
        }
        catch (const std::exception &e)
        {
            _printer->printError(std::string("[Client] Failed to print request: ") + e.what());
            throw exceptions::GrpcException(std::string("Failed to send request: ") + e.what());
        }

        if (status.ok())
        {
            if (response.error_code() == ::app_calculator::grpc::ErrorCode::OK)
            {
                _printer->printInfo("[Client] Result: " + std::to_string(response.result()));
                _printer->printInfo("[Client] Status: " + response.status());
            }
            else
            {
                _printer->printError(
                    std::string("[Client] Error: code=") +
                    std::to_string(response.error_code()) +
                    ", name=" + app_calculator::utils::network_utils::errorCodeToString(response.error_code()) +
                    ", message=" + response.error_message());
            }
        }
        else
        {
            _printer->printError(
                std::string("[Client] RPC failed: code=") +
                std::to_string(static_cast<int>(status.error_code())) +
                ", name=" + app_calculator::utils::network_utils::grpcStatusCodeToString(status.error_code()) +
                ", message=" + status.error_message());

            throw exceptions::GrpcException(status.error_message());
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

        throw exceptions::NetworkException("ClientRunner encountered an error: " +
                                           std::string(e.what()));
    }
    catch (...)
    {
        if (_printer)
        {
            _printer->printError("An unknown error occurred in ClientRunner.");
        }

        throw exceptions::NetworkException("ClientRunner encountered an unknown error.");
    }
}

} // namespace app_calculator::runner
