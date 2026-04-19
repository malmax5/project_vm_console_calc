#include "network/CalculatorServiceImpl.hpp"

#include "core/Exceptions.hpp"
#include "models/CalculationTask.hpp"
#include "utils/ErrorCodeUtils.hpp"

#include <vector>

namespace app_calculator::network
{

CalculatorServiceImpl::CalculatorServiceImpl(std::unique_ptr<core::ICalculator> calculator,
                                             std::unique_ptr<core::IChecker> checker,
                                             std::shared_ptr<core::IPrinter> printer)
    : _calculator(std::move(calculator)), _checker(std::move(checker)), _printer(printer)
{
}

::grpc::Status
CalculatorServiceImpl::Calculate(::grpc::ServerContext *context,
                                 const ::app_calculator::grpc::CalculationRequest *request,
                                 ::app_calculator::grpc::CalculationResponse *response)
{
    try
    {
        std::string operation = request->operation();
        std::vector<long long> operands(request->operands().begin(), request->operands().end());

        _printer->printInfo("Received RPC request with operation: " + request->operation() +
                            " and operands: " + std::to_string(request->operands().size()));

        models::CalculationTask task{operation, operands};

        _checker->check(task);
        long long result = _calculator->calculate(task);

        response->set_result(result);
        response->set_error_code(::app_calculator::grpc::ErrorCode::OK);
        response->set_error_message("");
        response->set_status("Success");

        return ::grpc::Status::OK;
    }
    catch (const std::exception &ex)
    {
        auto code = app_calculator::utils::network_utils::exceptionToErrorCode(ex);
        response->set_error_code(code);
        response->set_error_message(ex.what());
        response->set_status(std::string("Error: ") + ex.what());
        return ::grpc::Status::OK;
    }
    catch (...)
    {
        response->set_error_code(app_calculator::grpc::ErrorCode::INTERNAL_ERROR);
        response->set_error_message("An unknown error occurred.");
        response->set_status("Error: An unknown error occurred.");
        return ::grpc::Status::OK;
    }
}

} // namespace app_calculator::network
