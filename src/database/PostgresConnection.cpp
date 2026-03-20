#include "database/PostgresConnection.hpp"

#include <stdexcept>

namespace app_calculator::database
{

PostgresConnection::PostgresConnection(const std::string &connInfo)
    : _connection(PQconnectdb(connInfo.c_str()))
{
    checkConnection();
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

        throw std::runtime_error("Database connection failed: " + err);
    }
}

DbResult PostgresConnection::execute(const std::string &query)
{
    checkConnection();

    PGresult *rawResult = PQexec(_connection.get(), query.c_str());
    DbResult result(rawResult);

    result.checkError();

    return result;
}

} // namespace app_calculator::database
