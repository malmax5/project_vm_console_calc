#pragma once

#include "core/IParser.hpp"
#include <memory>

namespace app_calculator::parser
{

class JsonParser : public core::IParser
{
public:
    JsonParser();
    ~JsonParser() override;

    JsonParser(const JsonParser&) = delete;
    JsonParser& operator=(JsonParser&) = delete;

    models::CalculationTask parse(std::string_view input_data) override;

private:
    struct Impl;

private:
    std::unique_ptr<Impl> pimpl;
};

}
