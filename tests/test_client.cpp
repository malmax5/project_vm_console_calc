#include <grpcpp/grpcpp.h>
#include <gtest/gtest.h>
#include <thread>
#include <vector>

#include "calculator.grpc.pb.h"
#include "core/Constants.hpp"

void runClient(const std::string &operation, const std::vector<long long> &operands,
               const std::string &address, bool expectOk, bool expectTimeout = false)
{
    auto channel = ::grpc::CreateChannel(address, ::grpc::InsecureChannelCredentials());
    auto stub = ::app_calculator::grpc::CalculatorService::Stub(channel);

    ::app_calculator::grpc::CalculationRequest request;
    request.set_operation(operation);
    for (const auto &operand : operands)
    {
        request.add_operands(operand);
    }

    ::app_calculator::grpc::CalculationResponse response;
    ::grpc::ClientContext context;

    if (expectTimeout)
    {
        context.set_deadline(std::chrono::system_clock::now() +
                             std::chrono::milliseconds(app_calculator::core::defaultTimeoutMs));
    }

    ::grpc::Status status = stub.Calculate(&context, request, &response);

    if (expectTimeout)
    {
        EXPECT_EQ(status.error_code(), grpc::StatusCode::DEADLINE_EXCEEDED);
    }
    else if (expectOk)
    {
        EXPECT_TRUE(status.ok());
    }
    else
    {
        EXPECT_FALSE(status.ok());
    }
}

TEST(CalculatorGrpcTest, MultiThreadedOperations)
{
    std::vector<std::thread> clientThreads;
    std::string address = "0.0.0.0:50051";

    clientThreads.emplace_back(runClient, "sum", std::vector<long long>{10, 2}, address, true,
                               false);
    clientThreads.emplace_back(runClient, "sub", std::vector<long long>{50, 3}, address, true,
                               false);
    clientThreads.emplace_back(runClient, "div", std::vector<long long>{100, 2}, address, true,
                               false);
    clientThreads.emplace_back(runClient, "mul", std::vector<long long>{30, 4}, address, true,
                               false);
    clientThreads.emplace_back(runClient, "unknown_opp", std::vector<long long>{10, 2}, address,
                               false, false);
    clientThreads.emplace_back(runClient, "div", std::vector<long long>{10, 0}, address, false,
                               false);

    for (auto &thread : clientThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

TEST(CalculatorGrpcTest, HughLoadTest)
{
    std::vector<std::thread> clientThreads;
    std::string address = "0.0.0.0:50051";

    int aArg = 1;
    int bArg = 2;
    for (size_t i = 0; i < 100; ++i)
    {
        clientThreads.emplace_back(runClient, "sum", std::vector<long long>{aArg++, bArg++},
                                   address, true, false);
    }

    for (auto &thread : clientThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}
