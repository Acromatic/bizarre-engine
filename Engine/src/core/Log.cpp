#include "Log.h"

#include "BeAssert.h"
#include "containers/BeString.h"
#include "Defines.h"

#include <bits/types/time_t.h>
#include <cstdio>
#include <ctime>
#include <ostream>

namespace BE {

static LogLevel s_LogLevel = LogLevel::Trace;
static char* s_LogFilePath = nullptr;

static FILE* s_LogFileHandle = nullptr;

static const char* s_LogLevelNames[6]  = {"TRACE", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};
static const char* s_LogLevelColors[6] = {
    "\033[37;2m", "\033[36m", "\033[32m", "\033[33m", "\033[31m", "\033[1;31;4m"};
static const char* s_ColorReset = "\033[0m";

LogLevel GetLogLevel() {
  return s_LogLevel;
}

const char* GetLogLevelName(LogLevel level) {
  return s_LogLevelNames[(be_size)level];
}

String GetTimeString() {
  time_t rawTime;
  time(&rawTime);
  tm* timeInfo = localtime(&rawTime);
  char timeString[32];
  strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);
  return String(timeString);
}

void LogToConsole(LogLevel level, const String& logMessage) {
  FILE* output = level > LogLevel::Error ? stderr : stdout;
  fprintf(output, "%s%s%s\n", s_LogLevelColors[(be_size)level], logMessage.Data(), s_ColorReset);
  fflush(output);
}

void LogToFile(LogLevel level, const String& logMessage) {
  if (!s_LogFileHandle)
    return;

  fprintf(s_LogFileHandle, "%s\n", logMessage.Data());
}

void InitLogging(LogLevel minLevel) {
  s_LogLevel = minLevel;

  time_t rawTime;
  time(&rawTime);
  tm* timeInfo = localtime(&rawTime);
  char timeString[32];
  strftime(timeString, sizeof(timeString), "%Y-%m-%d_%H:%M:%S", timeInfo);

  char buffer[128]{0};
  snprintf(buffer, sizeof(buffer), "log-%s.txt", timeString);
  s_LogFilePath   = buffer;
  s_LogFileHandle = fopen(s_LogFilePath, "w");
  if (!s_LogFileHandle) {
    fprintf(stderr, "Failed to open log file: %s\n", s_LogFilePath);
  }
}

void ShutdownLogging() {
  if (s_LogFileHandle) {
    fclose(s_LogFileHandle);
  }
}

void ReportFailedAssert(const char* expression, const char* file, int line, const char* msg) {
  if (msg) {
    LOG_FATAL("Assertion failed: %s\n\tFile: %s:%d", msg, file, line);
  } else {
    LOG_FATAL("Assertion failed: %s\n\tFile: %s:%d", expression, file, line);
  }
}

} // namespace BE
