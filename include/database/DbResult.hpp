#pragma once
#include <libpq-fe.h>

#include <memory>
#include <string>

namespace app_calculator::database
{

struct PgResultDeleter
{
  public:
    void operator()(PGresult *res) const
    {
        if (res != nullptr)
        {
            PQclear(res);
        }
    }
};

class DbResult
{
  public:
    explicit DbResult(PGresult *res);
    ~DbResult() = default;

    DbResult(const DbResult &) = delete;
    DbResult &operator=(const DbResult &) = delete;
    DbResult(DbResult &&) noexcept = default;
    DbResult &operator=(DbResult &&) noexcept = default;

    bool isSuccessful() const;
    int rowCount() const;
    std::string getValue(int row, int column) const;
    void checkError() const;

  private:
    std::unique_ptr<PGresult, PgResultDeleter> _result;
};

} // namespace app_calculator::database
