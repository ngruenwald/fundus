#pragma once

//
// NOTE: You need to include common/log.ipp (or common/logger/logger_tools.ipp)
//       in one of your projects implementation files.
//

#include <sstream>
#include <string>

namespace cmn {
namespace log {
namespace tools {

/// Log level formatting
struct LogLevelFormat
{
    int level;
    std::string text;
};

std::ostream& operator<<(std::ostream& oss, const LogLevelFormat& llf);

/// Shorten the given path.
std::string strip_path(const std::string& input, int keep = 0);

/// Current time formatted as string
std::string get_time_stamp();

/// Stack trace
#ifdef HAVE_TRACE
std::string get_trace(int offset = 0, int count = -1);
#endif // HAVE_TRACE

} // namespace tools
} // namespace log
} // namespace cmn
