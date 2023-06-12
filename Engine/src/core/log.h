#pragma once

namespace BE {
enum class LogLevel {
  Trace,
  Debug,
  Info,
  Warning,
  Error,
  Fatal
};

void InitLogging(LogLevel minLevel);
void LogMessage(LogLevel level, const char* format, ...);
void ShutdownLogging();

#define LOG_FATAL(...) ::BE::LogMessage(::BE::LogLevel::Fatal, __VA_ARGS__)
#define LOG_ERROR(...) ::BE::LogMessage(::BE::LogLevel::Error, __VA_ARGS__)

#ifdef DEBUG
  #define LOG_WARN(...)  ::BE::LogMessage(::BE::LogLevel::Warning, __VA_ARGS__)
  #define LOG_INFO(...)  ::BE::LogMessage(::BE::LogLevel::Info, __VA_ARGS__)
  #define LOG_DEBUG(...) ::BE::LogMessage(::BE::LogLevel::Debug, __VA_ARGS__)
  #define LOG_TRACE(...) ::BE::LogMessage(::BE::LogLevel::Trace, __VA_ARGS__)
#else
  #define LOG_WARN(...)
  #define LOG_INFO(...)
  #define LOG_DEBUG(...)
  #define LOG_TRACE(...)
#endif

} // namespace BE
