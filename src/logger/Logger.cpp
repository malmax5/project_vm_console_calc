#include "logger/Logger.hpp"

#include <filesystem>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace app_calculator::logger
{

struct Logger::Impl
{
public:
    Impl()
    {
        std::filesystem::create_directories("logs");

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_level(spdlog::level::warn);
        consoleSink->set_pattern("[%^%l%$] %v");

        auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/calculator.log",
            1024 * 1024 * 5,
            3
        );
        fileSink->set_level(spdlog::level::trace);
        fileSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] %v");

        spdLogger = std::make_shared<spdlog::logger>(
            "multi_sink",
            spdlog::sinks_init_list{consoleSink, fileSink}
        );
        spdLogger->set_level(spdlog::level::trace);
        spdLogger->flush_on(spdlog::level::err);
    }

    std::shared_ptr<spdlog::logger> spdLogger;
};

Logger& Logger::instance()
{
    static Logger inst;
    return inst;
}

Logger::Logger()
    : pimpl(std::make_unique<Impl>())
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
