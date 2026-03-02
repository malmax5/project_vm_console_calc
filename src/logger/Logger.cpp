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

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::warn);
        console_sink->set_pattern("[%^%l%$] %v");

        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/calculator.log",
            1024 * 1024 * 5,
            3
        );
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] %v");

        spd_logger = std::make_shared<spdlog::logger>(
            "multi_sink",
            spdlog::sinks_init_list{console_sink, file_sink}
        );
        spd_logger->set_level(spdlog::level::trace);
        spd_logger->flush_on(spdlog::level::err);
    }

public:
    std::shared_ptr<spdlog::logger> spd_logger;
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
    pimpl->spd_logger->debug(message);
}

void Logger::info(std::string_view message)
{
    pimpl->spd_logger->info(message);
}

void Logger::warn(std::string_view message)
{
    pimpl->spd_logger->warn(message);
}

void Logger::error(std::string_view message)
{
    pimpl->spd_logger->error(message);
}

} // namespace app_calculator::logger
