#pragma once

#include "core/IParser.hpp"
#include <memory>

namespace app_calculator::parser
{

class JsonParser final : public core::IParser
{
  public:
    JsonParser();
    ~JsonParser() override;

    JsonParser(const JsonParser &) = delete;
    JsonParser &operator=(JsonParser &) = delete;
    JsonParser(JsonParser &&) noexcept = default;
    JsonParser &operator=(JsonParser &&) noexcept = default;

    models::CalculationTask parse(std::string_view inputData) override;

  private:
    struct Impl;

    std::unique_ptr<Impl> pimpl;
};

} // namespace app_calculator::parser
