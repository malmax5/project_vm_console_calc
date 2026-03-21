#pragma once
#include <optional>
#include <vector>

namespace app_calculator::core
{

template <typename T> class IRepository
{
  public:
    IRepository() = default;
    virtual ~IRepository() = default;

    IRepository(const IRepository &) = delete;
    IRepository &operator=(const IRepository &) = delete;
    IRepository(IRepository &&) noexcept = default;
    IRepository &operator=(IRepository &&) noexcept = default;

    virtual void add(const T &item) = 0;
    virtual std::vector<T> getAll() const = 0;
    virtual std::optional<int64_t> findResult(int64_t operandA, std::optional<int64_t> operandB,
                                              std::string_view operation) const = 0;
};

} // namespace app_calculator::core
