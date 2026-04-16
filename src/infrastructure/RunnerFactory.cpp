#include "infrastructure/RunnerFactory.hpp"

#include "runner/ClientRunner.hpp"
#include "runner/ConsoleRunner.hpp"
#include "runner/ServerRunner.hpp"
#include "network/CalculatorServiceImpl.hpp"

namespace app_calculator::infrastructure
{

std::unique_ptr<core::IRunner> RunnerFactory::createServerRunner(ServerRunnerDeps &deps)
{
    auto service = std::make_shared<network::CalculatorServiceImpl>(std::move(deps.calculator), std::move(deps.checker), deps.printer);
    return std::make_unique<runner::ServerRunner>(service);
}

std::unique_ptr<core::IRunner> RunnerFactory::createConsoleRunner(ConsoleRunnerDeps &deps)
{
    return std::make_unique<runner::ConsoleRunner>(deps);
}

std::unique_ptr<core::IRunner> RunnerFactory::createClientRunner(ClientRunnerDeps &deps)
{
    auto channel = ::grpc::CreateChannel(deps.serverAddress, ::grpc::InsecureChannelCredentials());
    return std::make_unique<runner::ClientRunner>(channel, deps);
}

} // namespace app_calculator::infrastructure
