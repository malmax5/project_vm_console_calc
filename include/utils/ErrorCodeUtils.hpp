#pragma once

#include "calculator.grpc.pb.h"
#include <core/Exceptions.hpp>
#include <string>

namespace app_calculator::utils::network_utils
{

inline app_calculator::grpc::ErrorCode exceptionToErrorCode(const std::exception &exception)
{
    using namespace app_calculator::exceptions;
    if (dynamic_cast<const ValidationException *>(&exception) != nullptr)
    {
        return app_calculator::grpc::ErrorCode::VALIDATION_ERROR;
    }
    if (dynamic_cast<const CalculationException *>(&exception) != nullptr)
    {
        return app_calculator::grpc::ErrorCode::CALCULATION_ERROR;
    }
    if (dynamic_cast<const DatabaseException *>(&exception) != nullptr ||
        dynamic_cast<const ConnectionException *>(&exception) != nullptr ||
        dynamic_cast<const QueryException *>(&exception) != nullptr)
    {
        return app_calculator::grpc::ErrorCode::DB_ERROR;
    }
    if (dynamic_cast<const ConfigException *>(&exception) != nullptr)
    {
        return app_calculator::grpc::ErrorCode::CONFIG_ERROR;
    }
    if (dynamic_cast<const GrpcException *>(&exception) != nullptr ||
        dynamic_cast<const NetworkException *>(&exception) != nullptr ||
        dynamic_cast<const NetworkTimeoutException *>(&exception) != nullptr)
    {
        return app_calculator::grpc::ErrorCode::NETWORK_ERROR;
    }

    return app_calculator::grpc::ErrorCode::INTERNAL_ERROR;
}

inline std::string errorCodeToString(app_calculator::grpc::ErrorCode code)
{
    switch (code)
    {
        case app_calculator::grpc::ErrorCode::OK:
            return "OK";
        case app_calculator::grpc::ErrorCode::VALIDATION_ERROR:
            return "VALIDATION_ERROR";
        case app_calculator::grpc::ErrorCode::CALCULATION_ERROR:
            return "CALCULATION_ERROR";
        case app_calculator::grpc::ErrorCode::DB_ERROR:
            return "DB_ERROR";
        case app_calculator::grpc::ErrorCode::CONFIG_ERROR:
            return "CONFIG_ERROR";
        case app_calculator::grpc::ErrorCode::NETWORK_ERROR:
            return "NETWORK_ERROR";
        case app_calculator::grpc::ErrorCode::INTERNAL_ERROR:
            return "INTERNAL_ERROR";
        default:
            return "UNKNOWN_ERROR_CODE";
    }
}

} // namespace app_calculator::utils::network_utils
