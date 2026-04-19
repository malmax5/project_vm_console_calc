#pragma once

namespace app_calculator::core
{

inline constexpr char defaultServerAddress[] = "0.0.0.0:50051";
inline constexpr char defaultClientAddress[] = "localhost:50051";
inline constexpr char configPath[] = "/etc/calculator/config.json";
inline constexpr char logDir[] = "logs/";
inline constexpr char logFile[] = "logs/calculator.log";
inline constexpr char systemdLogFile[] = "/var/log/app_calculator.log";

inline constexpr long signalWaitNanoseconds = 300'000'000;
inline constexpr int defaultTimeoutMs = 5000;

} // namespace app_calculator::core
