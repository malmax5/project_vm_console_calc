#include "network/CalculatorServiceImpl.hpp"

#include "core/Exceptions.hpp"
#include "models/CalculationTask.hpp"

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
        response->set_status("Success");

        return ::grpc::Status::OK;
    }
    catch (const exceptions::ValidationException &validationException)
    {
        response->set_status(std::string("Validation error: ") + validationException.what());
        return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, validationException.what());
    }
    catch (const exceptions::CalculationException &calculationException)
    {
        response->set_status(std::string("Calculation error: ") + calculationException.what());
        return ::grpc::Status(::grpc::StatusCode::FAILED_PRECONDITION, calculationException.what());
    }
    catch (const std::exception &exception)
    {
        response->set_status(std::string("Error: ") + exception.what());
        return ::grpc::Status(::grpc::StatusCode::INTERNAL, exception.what());
    }
    catch (...)
    {
        response->set_status("Unknown error occurred.");
        return ::grpc::Status(::grpc::StatusCode::UNKNOWN, "Unknown error occurred.");
    }
}

} // namespace app_calculator::network
