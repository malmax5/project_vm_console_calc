#include "parser/JsonParser.hpp"

#include "core/Exceptions.hpp"
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace app_calculator::models
{

// NOLINTNEXTLINE(readability-identifier-naming)
void to_json(nlohmann::json& jsonData, const CalculationTask& task)
{
    jsonData = nlohmann::json{{"operation", task.operation}, {"operands", task.operands}};
}

// NOLINTNEXTLINE(readability-identifier-naming)
void from_json(const nlohmann::json& jsonData, CalculationTask& task)
{
    jsonData.at("operation").get_to(task.operation);
    jsonData.at("operands").get_to(task.operands);
}

} // namespace app_calculator::models

namespace app_calculator::parser
{

struct JsonParser::Impl
{
public:
    models::CalculationTask parseInternal(std::string_view inputData)
    {
        try
        {
            nlohmann::json jsonData = nlohmann::json::parse(inputData);

            return jsonData.get<models::CalculationTask>();
        }
        catch(const nlohmann::json::parse_error& e)
        {
            throw exceptions::ParserException("Synax error: " + std::string(e.what()));
        }
        catch(const nlohmann::json::type_error& e)
        {
            throw exceptions::ParserException("Type mismatch: " + std::string(e.what()));
        }
        catch(const nlohmann::json::out_of_range& e)
        {
            throw exceptions::ParserException("Missing required field: " + std::string(e.what()));
        }
    }
};

JsonParser::JsonParser()
    : pimpl(std::make_unique<Impl>())
{

}

JsonParser::~JsonParser()
{

}

models::CalculationTask JsonParser::parse(std::string_view inputData)
{
    return pimpl->parseInternal(inputData);
}

} // namespace app_calculator::parser
