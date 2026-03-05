#pragma once

#include "models/CalculationTask.hpp"
#include <string_view>

namespace app_calculator::core
{

class IParser
{
  public:
    IParser() = default;
    virtual ~IParser() = default;

    IParser(const IParser &) = delete;
    IParser &operator=(const IParser &) = delete;
    IParser(IParser &&) noexcept = delete;
    IParser &operator=(IParser &&) noexcept = delete;

    virtual models::CalculationTask parse(std::string_view inputData) = 0;
};

} // namespace app_calculator::core
