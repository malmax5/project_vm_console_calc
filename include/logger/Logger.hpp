#pragma once

#include "logger/ILogger.hpp"
#include <memory>

namespace app_calculator::logger
{

class Logger : public ILogger
{
  public:
    static Logger &instance();

    ~Logger() override;

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
    Logger(Logger &&) noexcept = default;
    Logger &operator=(Logger &&) noexcept = default;

    void debug(std::string_view message) override;
    void info(std::string_view message) override;
    void warn(std::string_view message) override;
    void error(std::string_view message) override;

  private:
    Logger();

    struct Impl;

    std::unique_ptr<Impl> pimpl;
};

} // namespace app_calculator::logger
