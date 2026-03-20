#include "core/IDbConnection.hpp"

#include "database/DbResult.hpp"

#include <memory>

namespace app_calculator::database
{

class PostgresConnection final : public core::IDbConnection<DbResult>
{
  public:
    explicit PostgresConnection(const std::string &connInfo);

    DbResult execute(const std::string &query) override;
    bool isConnected() const override;

  private:
    struct PgConnDeleter
    {
        void operator()(PGConn *conn) const
        {
            if (conn != nullptr)
            {
                PQfinish(conn);
            }
        }
    };

    std::unique_ptr<PGconn, PgConnDeleter> _connection;
};

} // namespace app_calculator::database
