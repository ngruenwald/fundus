#pragma once

#if (_LOG_LOGGER == _LOG_STDOUT_LOGGING) || (_LOG_LOGGER == _LOG_SYSLOG_LOGGING)

#include <common/log.hpp>
#include <common/logger/logger_tools.ipp>

namespace cmn {
namespace log {

int MIN_LEVEL = LVL_TRACE;

} // namespace log
} // namespace cmn

#endif // _LOG_LOGGER
