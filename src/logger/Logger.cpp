#include "logger/Logger.hpp"

#include <filesystem>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace app_calculator::logger
{

struct Logger::Impl
{
  public:
    static constexpr std::size_t bytesInMb = static_cast<const std::size_t>(1024 * 1024);
    static constexpr std::size_t maxLogFileSize = static_cast<const std::size_t>(5 * bytesInMb);
    static constexpr std::size_t maxLogFiles = static_cast<const std::size_t>(3);

    Impl()
    {
        std::filesystem::create_directories("logs");

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_level(spdlog::level::trace);
        consoleSink->set_pattern("[%^%l%$] %v");

        auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/calculator.log", maxLogFileSize, maxLogFiles);
        fileSink->set_level(spdlog::level::trace);
        fileSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] %v");

        spdLogger = std::make_shared<spdlog::logger>(
            "multi_sink", spdlog::sinks_init_list{consoleSink, fileSink});
        spdLogger->set_level(spdlog::level::trace);
        spdLogger->flush_on(spdlog::level::err);
    }

    std::shared_ptr<spdlog::logger> spdLogger;
};

std::shared_ptr<ILogger> Logger::instance()
{
    static std::shared_ptr<ILogger> inst(new Logger());
    return inst;
}

Logger::Logger() : pimpl(std::make_unique<Impl>())
{
}

Logger::~Logger()
{
    spdlog::shutdown();
}

void Logger::debug(std::string_view message)
{
    pimpl->spdLogger->debug(message);
}

void Logger::info(std::string_view message)
{
    pimpl->spdLogger->info(message);
}

void Logger::warn(std::string_view message)
{
    pimpl->spdLogger->warn(message);
}

void Logger::error(std::string_view message)
{
    pimpl->spdLogger->error(message);
}

} // namespace app_calculator::logger
