#include "database/repositories/HistoryRepository.hpp"

namespace app_calculator::database
{

HistoryRepository::HistoryRepository(std::shared_ptr<core::IDbAccessor<database::DbResult>> dbAccessor)
    : _dbAccessor(dbAccessor)
{   
}

void HistoryRepository::add(const models::Calculation &item)
{
    std::string operandAStr = std::to_string(item.operandA);
    std::string operandBStr = item.operandB ? std::to_string(*item.operandB) : "";
    std::string operationStr = item.operation;
    std::string resultStr = item.result ? std::to_string(*item.result) : "";
    std::string statusStr = std::to_string(static_cast<int>(item.status));

    std::vector<const char *> params;
    params.push_back(operandAStr.c_str());
    params.push_back(item.operandB ? operandBStr.c_str() : nullptr);
    params.push_back(operationStr.c_str());
    params.push_back(item.result ? resultStr.c_str() : nullptr);
    params.push_back(statusStr.c_str());

    std::string query = R"(
        INSERT INTO calculation_history (operand_a, operand_b, operation, result, status_id)
        VALUES ($1, $2, $3, $4, $5)
        ON CONFLICT (operand_a, operand_b, operation) DO NOTHING;)";

    _dbAccessor->executeParams(query, params);
}

std::vector<models::Calculation> HistoryRepository::getAll() const
{
    std::string query =
        "SELECT operand_a, operand_b, operation, result, status_id FROM calculation_history;";

    auto res = _dbAccessor->execute(query);
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
    std::string query;
    std::vector<const char *> params;
    std::string operandAStr = std::to_string(operandA);
    std::string operandBStr;
    std::string operationStr(operation);
    std::string statusStr = std::to_string(static_cast<int>(models::OperationStatus::success));

    if (operandB.has_value())
    {
        query = R"(
            SELECT result FROM calculation_history
            WHERE operand_a = $1 AND operand_b = $2 AND operation = $3 AND status_id = $4
            ORDER BY created_at DESC LIMIT 1;)";

        operandBStr = std::to_string(*operandB);
        params = {operandAStr.c_str(), operandBStr.c_str(), operationStr.c_str(),
                  statusStr.c_str()};
    }
    else
    {
        query = R"(
            SELECT result FROM calculation_history
            WHERE operand_a = $1 AND operand_b IS NULL AND operation = $2 AND status_id = $3
            ORDER BY created_at DESC LIMIT 1;)";
        params = {operandAStr.c_str(), operationStr.c_str(), statusStr.c_str()};
    }

    auto res = _dbAccessor->executeParams(query, params);

    std::optional<int64_t> result = std::nullopt;
    if (res.rowCount() > 0 && !res.getValue(0, 0).empty())
    {
        result = std::stoll(res.getValue(0, 0));
    }

    return result;
}

} // namespace app_calculator::database
