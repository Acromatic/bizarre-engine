#pragma once

#include "containers/BeString.h"
#include "utils/StringFormat.h"
#include "utils/TypeUtils.h"

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

template<typename... Args>
void LogMessage(LogLevel level, const String& format, Args... args);

void ShutdownLogging();

LogLevel GetLogLevel();
const char* GetLogLevelName(LogLevel level);
String GetTimeString();
void LogToConsole(LogLevel level, const String& logMessage);
void LogToFile(LogLevel level, const String& logMesage);

template<typename... Args>
void LogMessage(LogLevel level, const String& format, Args... args) {
  if (level < GetLogLevel()) {
    return;
  }

  String formattedMsg = Format(format, args...);
  String logMessage = Format("[{}] {}: {}", GetTimeString(), GetLogLevelName(level), formattedMsg);

  LogToConsole(level, logMessage);
  LogToFile(level, logMessage);
}

} // namespace BE

#if 1
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
#else
  #define LOG_FATAL(...)
  #define LOG_ERROR(...)
  #define LOG_WARN(...)
  #define LOG_INFO(...)
  #define LOG_TRACE(...)
#endif
