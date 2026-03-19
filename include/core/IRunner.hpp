#pragma once

namespace app_calculator::core
{

class IRunner
{
  public:
    IRunner() = default;
    virtual ~IRunner() = default;

    IRunner(const IRunner &) = delete;
    IRunner &operator=(const IRunner &) = delete;
    IRunner(IRunner &&) noexcept = default;
    IRunner &operator=(IRunner &&) noexcept = default;

    virtual void run(int argc, char **argv) = 0;
};

} // namespace app_calculator::core
