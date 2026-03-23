#include "core/IDbConnection.hpp"

#include "database/DbResult.hpp"

#include <memory>

namespace app_calculator::database
{

class PostgresConnection final : public core::IDbConnection<DbResult>
{
  public:
    explicit PostgresConnection(const std::string &connInfo);
    ~PostgresConnection() override = default;

    PostgresConnection(const PostgresConnection &) = delete;
    PostgresConnection &operator=(PostgresConnection &) = delete;
    PostgresConnection(PostgresConnection &&) noexcept = default;
    PostgresConnection &operator=(PostgresConnection &&) noexcept = default;

    DbResult execute(const std::string &query) override;
    bool isConnected() const override;

  private:
    struct PgConnDeleter
    {
        void operator()(PGconn *conn) const
        {
            if (conn != nullptr)
            {
                PQfinish(conn);
            }
        }
    };

    void checkConnection() const;
    void initializeSchema();

    std::unique_ptr<PGconn, PgConnDeleter> _connection;
};

} // namespace app_calculator::database
