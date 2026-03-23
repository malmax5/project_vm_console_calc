#include "database/repositories/HistoryRepository.hpp"

#include <fmt/core.h>

namespace app_calculator::database
{

void HistoryRepository::add(const models::Calculation &item)
{
    std::string valueB = item.operandB ? std::to_string(*item.operandB) : "NULL";
    std::string valueResult = item.result ? std::to_string(*item.result) : "NULL";

    std::string query = fmt::format(
        "INSERT INTO calculation_history (operand_a, operand_b, operation, result, status_id) "
        "VALUES ({}, {}, '{}', {}, {})"
        "ON CONFLICT (operand_a, operand_b, operation) DO NOTHING;",
        item.operandA, valueB, item.operation, valueResult, static_cast<int>(item.status));

    getDbConnection().execute(query);
}

std::vector<models::Calculation> HistoryRepository::getAll() const
{
    std::string query = fmt::format(
        "SELECT operand_a, operand_b, operation, result, status_id FROM calculation_history;");

    auto res = getDbConnection().execute(query);
    std::vector<models::Calculation> history;
    history.reserve(res.rowCount());

    for (int i = 0; i < res.rowCount(); i++)
    {
        models::Calculation calc;
        calc.operandA = std::stoll(res.getValue(i, 0));

        std::string operandBString = res.getValue(i, 1);
        if (!operandBString.empty())
        {
            calc.operandB = std::stoll(operandBString);
        }

        calc.operation = res.getValue(i, 2);

        std::string resultString = res.getValue(i, 3);
        if (!resultString.empty())
        {
            calc.result = std::stoll(resultString);
        }

        calc.status = static_cast<models::OperationStatus>(std::stoi(res.getValue(i, 4)));

        history.push_back(std::move(calc));
    }

    return history;
}

std::optional<int64_t> HistoryRepository::findResult(int64_t operandA,
                                                     std::optional<int64_t> operandB,
                                                     std::string_view operation) const
{
    std::string valueB = operandB ? fmt::format("= {}", *operandB) : "IS NULL";

    std::string query = fmt::format("SELECT result FROM calculation_history "
                                    "WHERE operand_a = {} AND operand_b {} AND operation = '{}' "
                                    "AND status_id = {} "
                                    "ORDER BY created_at DESC LIMIT 1;",
                                    operandA, valueB, operation,
                                    static_cast<int>(models::OperationStatus::success));

    auto res = getDbConnection().execute(query);

    std::optional<int64_t> result = std::nullopt;
    if (res.rowCount() > 0 && !res.getValue(0, 0).empty())
    {
        result = std::stoll(res.getValue(0, 0));
    }

    return result;
}

} // namespace app_calculator::database
