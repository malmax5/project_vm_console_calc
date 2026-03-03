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
    models::CalculationTask parseInternal(std::string_view input_data)
    {
        try
        {
            nlohmann::json j = nlohmann::json::parse(input_data);

            models::CalculationTask task;

            if (j.contains("operations") && j["operations"].is_string())
            {
                task.operation = j.at("operations").get<std::string>();
            }
            else
            {
                throw exceptions::ParserException("JSON missing 'operation' field or it is no a string");
            }

            if (j.contains("operands") && j["operands"].is_array())
            {
                for (const auto& item : j.at("operands"))
                {
                    if (item.is_number_integer())
                    {
                        task.operands.push_back(item.get<long long>());
                    }
                    else
                    {
                        throw exceptions::ParserException("Operand is not an integer number");
                    }
                }
            }
            else
            {
                throw exceptions::ParserException("JSON missin 'operands' or it is not an array");
            }

            return task;
        }
        catch(const nlohmann::json::parse_error& e)
        {
            throw exceptions::ParserException(std::string("JSON Parse Error: ") + e.what());
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

models::CalculationTask JsonParser::parse(std::string_view input_data)
{
    return pimpl->parseInternal(input_data);
}

} // namespace app_calculator::parser
