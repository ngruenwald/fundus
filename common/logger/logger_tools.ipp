#pragma once

#include <common/log.hpp>
#include <common/logger/logger_tools.hpp>

#include <chrono>

#ifdef HAVE_TRACE
#include <cxxabi.h>
#include <execinfo.h>
#endif

#ifdef HAVE_RANG
#include <rang.hpp>
#endif

namespace cmn {
namespace log {
namespace tools {

// Log level formatting
std::ostream& operator<<(
    std::ostream& oss,
    const LogLevelFormat& llf)
{
#ifdef HAVE_RANG
    switch (llf.level)
    {
        case LVL_TRACE:
            oss << rang::style::dim
                << rang::style::italic
                << rang::fg::gray;
            break;

        case LVL_DEBUG:
            oss << rang::style::dim
                << rang::fg::gray;
            break;

        case LVL_INFO:
            oss << rang::fgB::gray;
            break;

        case LVL_WARN:
            oss << rang::fgB::yellow;
            break;

        case LVL_ERROR:
            oss << rang::fgB::red;
            break;

        case LVL_FATAL:
            oss << rang::bg::red
                << rang::fgB::yellow
                << rang::style::bold
                << rang::style::blink;
            break;

        case LVL_NOTIF:
            oss << rang::fgB::green;
            break;

        default:
            oss << rang::fg::cyan;
            break;
    }
#endif // HAVE_RANG

    oss << llf.text;

#ifdef HAVE_RANG
    oss << rang::style::reset;
#endif // HAVE_RANG

    return oss;
}

// Shorten the given path.
std::string strip_path(
    const std::string& input,
    int keep)
{
    std::string::size_type idx = input.length() + 1;

    do
    {
        idx = input.find_last_of("/\\", idx - 1);

    } while (--keep >= 0 && idx != std::string::npos);

    if (idx == std::string::npos)
    {
        return input;
    }

    return input.substr(idx + 1);
}

// Formatted time
std::string get_time_stamp()
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_c);

    auto dur = now.time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    char buffer[32];
    auto len = std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &now_tm);
    sprintf(buffer + len, ".%04u", ms % 10000);
    return buffer;
}

// Stack trace
#ifdef HAVE_TRACE
std::string get_trace(
    int offset,
    int count)
{
#ifdef WIN32
    return "no trace";
#else // WIN32

    const int buffer_count = 100;

    offset += 1;    // top entry is this method

    if (count == -1)
    {
        count = buffer_count;
    }
    else
    {
        count += offset;

        if (count > buffer_count)
        {
            count = buffer_count;
        }
    }

    void* buffer[buffer_count];

    int nptrs = backtrace(buffer, count);

    if (nptrs <= offset)
    {
        return "no trace";
    }

    char** strings = backtrace_symbols(buffer, nptrs);

    if (strings == nullptr)
    {
        return "no symbols";
    }

    std::ostringstream trace;

    for (int n = offset; n < nptrs; n++)
    {
        auto beg = strrchr(strings[n], '(');
        if (!beg) continue;
        beg++;

        auto end = strrchr(beg, ')');
        if (!end) continue;
        *end = '\0';

        end = strrchr(beg, '+');
        if (end) *end = '\0';

        if (end <= beg) continue;

        int status;
        char* dm = abi::__cxa_demangle(beg, nullptr, nullptr, &status);

        trace << "[" << (n - offset) << "] " << (status == 0 ? dm : beg) << "\n";

        free(dm);
    }

    free(strings);

    return trace.str();
#endif // WIN32
}
#endif // HAVE_TRACE

} // namespace tools
} // namespace log
} // namespace cmn
