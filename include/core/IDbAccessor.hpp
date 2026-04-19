#pragma once

#include <string>
#include <vector>

namespace app_calculator::core
{

template <typename TResult>
class IDbAccessor
{
public:
    IDbAccessor() = default;
    virtual ~IDbAccessor() = default;

    IDbAccessor(const IDbAccessor &) = delete;
    IDbAccessor &operator=(const IDbAccessor &) = delete;
    IDbAccessor(IDbAccessor &&) noexcept = default;
    IDbAccessor &operator=(IDbAccessor &&) noexcept = default;

    virtual TResult execute(const std::string &query) = 0;
    virtual TResult executeParams(const std::string &query, const std::vector<const char *> &params) = 0;
};

}
