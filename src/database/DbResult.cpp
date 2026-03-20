#include "database/DbResult.hpp"

#include <stdexcept>

namespace app_calculator::database
{

DbResult::DbResult(PGresult *res) : _result(res)
{
}

bool DbResult::isSuccessful() const
{
    if (!_result)
    {
        return false;
    }

    ExecStatusType status = PQresultStatus(_result.get());

    return status == PGRES_COMMAND_OK || status == PGRES_TUPLES_OK;
}

int DbResult::rowCount() const
{
    if (!_result)
    {
        return 0;
    }

    return PQntuples(_result.get());
}

std::string DbResult::getValue(int row, int column) const
{
    if (!_result)
    {
        return "";
    }

    return PQgetvalue(_result.get(), row, column);
}

void DbResult::checkError() const
{
    if (!isSuccessful())
    {
        std::string msg = "Empty result object";

        if (_result)
        {
            PQresultErrorMessage(_result.get());
        }

        throw std::runtime_error("Database error: " + msg);
    }
}

} // namespace app_calculator::database
