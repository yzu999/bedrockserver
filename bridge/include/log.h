#pragma once

#include <cstdlib>
#include <vector>
#include <cstdarg>

#define LogFuncDef(name, logLevel)                         \
  static void name(const char *tag, const char *text, ...) \
  {                                                        \
    va_list args;                                          \
    va_start(args, text);                                  \
    vlog(logLevel, tag, text, args);                       \
    va_end(args);                                          \
  }

enum class LogLevel
{
  LOG_TRACE = 0,
  LOG_DEBUG = 1,
  LOG_INFO = 2,
  LOG_NOTICE = 3,
  LOG_WARN = 4,
  LOG_ERROR = 5,
  LOG_FATAL = 6,
};

class Log
{

public:
  static inline const char *getLogLevelString(LogLevel lvl)
  {
    if (lvl == LogLevel::LOG_TRACE)
      return "Trace";
    if (lvl == LogLevel::LOG_DEBUG)
      return "Debug";
    if (lvl == LogLevel::LOG_INFO)
      return "Info";
    if (lvl == LogLevel::LOG_WARN)
      return "Warn";
    if (lvl == LogLevel::LOG_ERROR)
      return "Error";
    return "?";
  }

  static void vlog(LogLevel level, const char *tag, const char *text, va_list args);

  static void log(LogLevel level, const char *tag, const char *text, ...)
  {
    va_list args;
    va_start(args, text);
    vlog(level, tag, text, args);
    va_end(args);
  }

  LogFuncDef(trace, LogLevel::LOG_TRACE)
  LogFuncDef(debug, LogLevel::LOG_DEBUG)
  LogFuncDef(info, LogLevel::LOG_INFO)
  LogFuncDef(notice, LogLevel::LOG_NOTICE)
  LogFuncDef(warn, LogLevel::LOG_WARN)
  LogFuncDef(error, LogLevel::LOG_ERROR)
  LogFuncDef(fatal, LogLevel::LOG_FATAL)
};

#undef LogFuncDef