#pragma once

#include <sstream>
#include <common/logger/logger_tools.hpp>

#ifdef HAVE_FMTLIB
#include <fmt/format.h>
#endif

namespace cmn {
namespace log {

extern int MIN_LEVEL; // YOU need to define this in your code!

#define TRACE_(...)  _OUTPUT(LVL_TRACE, "TRACE", __VA_ARGS__)
#define DEBUG_(...)  _OUTPUT(LVL_DEBUG, "DEBUG", __VA_ARGS__)
#define INFO_(...)   _OUTPUT(LVL_INFO,  " INFO", __VA_ARGS__)
#define WARN_(...)   _OUTPUT(LVL_WARN,  " WARN", __VA_ARGS__)
#define ERROR_(...)  _OUTPUT(LVL_ERROR, "ERROR", __VA_ARGS__)
#define FATAL_(...)  _OUTPUT(LVL_FATAL, "FATAL", __VA_ARGS__)
#define NOTIFY_(...) _OUTPUT(LVL_NOTIF, "NOTIF", __VA_ARGS__)

#define _OUTPUT(level, severity, ...) \
    _OUTPUT_FL(level, severity, __FILE__, __LINE__, __VA_ARGS__)

#ifdef HAVE_FMTLIB

#define _OUTPUT_FL(level, severity, file, line, ...)                           \
    {                                                                          \
        if (level >= ::cmn::log::MIN_LEVEL)                                    \
        {                                                                      \
            ::fmt::print(                                                      \
                "{} | {} | {} --- {}:{}\n",                                    \
                severity,                                                      \
                ::cmn::log::tools::get_time_stamp(),                           \
                ::fmt::format(__VA_ARGS__),                                    \
                ::cmn::log::tools::strip_path(file, 0),                        \
                line                                                           \
            );                                                                 \
        }                                                                      \
    }

#else

#define _OUTPUT_FL(level, severity, file, line, x)                             \
    {                                                                          \
        if (level >= ::cmn::log::MIN_LEVEL)                                    \
        {                                                                      \
            ::std::ostringstream oss;                                          \
            oss << ::cmn::log::tools::LogLevelFormat{level, severity} << " | " \
                << ::cmn::log::tools::get_time_stamp()  << " | "               \
                << x << " --- "                                                \
                << ::cmn::log::tools::strip_path(file, 0) << ':'               \
                << line << '\n';                                               \
            ::std::cout << oss.str() << ::std::flush;                          \
        }                                                                      \
    }

#endif // HAVE_FMTLIB

} // namespace log
} // namespace cmn
