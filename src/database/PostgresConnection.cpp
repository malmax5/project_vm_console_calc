#include "database/PostgresConnection.hpp"

#include "core/Exceptions.hpp"

namespace app_calculator::database
{

PostgresConnection::PostgresConnection(const std::string &connInfo)
    : _connection(PQconnectdb(connInfo.c_str()))
{
    checkConnection();
    initializeSchema();
}

bool PostgresConnection::isConnected() const
{
    return _connection && (PQstatus(_connection.get()) == CONNECTION_OK);
}

void PostgresConnection::checkConnection() const
{
    if (!isConnected())
    {
        std::string err = "Unknown connection error";
        if (_connection)
        {
            err = PQerrorMessage(_connection.get());
        }

        throw exceptions::ConnectionException(err);
    }
}

void PostgresConnection::initializeSchema()
{
    execute(R"(
        CREATE TABLE IF NOT EXISTS operation_statuses (
            status_id INT PRIMARY KEY,
            status_name VARCHAR(50) NOT NULL
        );
    )");

    execute(R"(
        INSERT INTO operation_statuses (status_id, status_name) VALUES 
        (0, 'SUCCESS'), (1, 'DIVISION_BY_ZERO'), (2, 'OVERFLOW'), 
        (3, 'INVALID_OPERANDS'), (4, 'UNKNOWN_ERROR')
        ON CONFLICT (status_id) DO NOTHING;
    )");

    execute(R"(
        CREATE TABLE IF NOT EXISTS calculation_history (
            id SERIAL PRIMARY KEY,
            operand_a BIGINT NOT NULL,
            operand_b BIGINT,
            operation VARCHAR(10) NOT NULL,
            result BIGINT,
            status_id INT NOT NULL REFERENCES operation_statuses(status_id),
            created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
            CONSTRAINT unique_calculation_params UNIQUE (operand_a, operand_b, operation)
        );
    )");
}

DbResult PostgresConnection::execute(const std::string &query)
{
    checkConnection();

    DbResult result(PQexec(_connection.get(), query.c_str()));

    result.checkError();

    return result;
}

DbResult PostgresConnection::executeParams(const std::string &query,
                                           const std::vector<const char *> &params)
{
    checkConnection();

    int nParams = static_cast<int>(params.size());

    DbResult result(PQexecParams(_connection.get(), query.c_str(), nParams, nullptr, params.data(),
                                 nullptr, nullptr, 0));

    result.checkError();

    return result;
}

} // namespace app_calculator::database
