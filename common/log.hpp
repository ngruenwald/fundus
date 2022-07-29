#pragma once

// NOTE: When you use the stdout or syslog logger,
//       you need to include the common/log.ipp file
//       in one of your implementation files.

#include <cassert>
#include <sstream>

//
// Loggers
//

#ifndef _LOG_LOGGER
#if defined(HAVE_ILOGGING2)
#define _LOG_LOGGER _LOG_ILOGGING2_LOGGING
#elif defined(HAVE_ILOGGING)
#define _LOG_LOGGER _LOG_ILOGGIN_LOGGING
#elif defined(HAVE_SPDLOG)
#define _LOG_LOGGER _LOG_SPDLOG_LOGGING
#elif defined(HAVE_SYSLOG)
#define _LOG_LOGGER _LOG_SYSLOG_LOGGING
#else
#define _LOG_LOGGER _LOG_STDOUT_LOGGING
#endif
#endif

#define _LOG_SYSLOG_LOGGING      0
#define _LOG_STDOUT_LOGGING      1
#define _LOG_GLOG_LOGGING        2
#define _LOG_SPDLOG_LOGGING      3
#define _LOG_ILOGGING_LOGGING    4
#define _LOG_ILOGGING2_LOGGING   5

//
// Levels
//

#define LVL_TRACE 0
#define LVL_DEBUG 1
#define LVL_INFO  2
#define LVL_WARN  3
#define LVL_ERROR 4
#define LVL_FATAL 5
#define LVL_NOTIF 6

//
// Include logger
//

#if _LOG_LOGGER == _LOG_SYSLOG_LOGGING
#include <common/logger/syslog_logger.hpp>
#elif _LOG_LOGGER == _LOG_STDOUT_LOGGING
#include <common/logger/stdout_logger.hpp>
#elif _LOG_LOGGER == _LOG_GLOG_LOGGING
#include <common/logger/glog_logger.hpp>
#elif _LOG_LOGGER == _LOG_SPDLOG_LOGGING
#include <common/logger/spdlog_logger.hpp>
#elif _LOG_LOGGER == _LOG_ILOGGING_LOGGING
#include <common/logger/ilogging_logger.hpp>
#elif _LOG_LOGGER == _LOG_ILOGGING2_LOGGING
#include <common/logger/ilogging2_logger.hpp>
#else
#pragma message("logger not defined")
#include <common/logger/stdout_logger.hpp>
#endif

//
// Log macros
//

#define TRACE_IF(cond, x) _IF(cond, TRACE_(x))
#define DEBUG_IF(cond, x) _IF(cond, DEBUG_(x))
#define INFO_IF(cond, x)  _IF(cond, INFO_(x))
#define WARN_IF(cond, x)  _IF(cond, WARN_(x))
#define ERROR_IF(cond, x) _IF(cond, ERROR_(x))
#define FATAL_IF(cond, x) _IF(cond, FATAL_(x))

#define _IF(cond, action) { if (cond) { action; } }

#define _LOG_CHECK(cond, scond, x) \
    ERROR_IF(!(cond), "CHECK of " scond  " failed " << x); assert(cond);

#define LOG_CHECK(cond) _LOG_CHECK(cond, #cond, "") // TODO: __VA_ARGS__

#define CHECK_(cond) LOG_CHECK(cond)

