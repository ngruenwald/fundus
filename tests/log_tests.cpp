#include "doctest.h"

#include <iostream>
#include <regex>
#include <string.h>

#include "common/log.hpp"
#include "common/log.ipp"


class Redirect
{
public:
    Redirect(
        std::ostream& oss)
        : org_{oss}
        , sbf_{org_.rdbuf()}
    {
        org_.rdbuf(out_.rdbuf());
    }

    ~Redirect()
    {
        org_.rdbuf(sbf_);
    }

    std::ostringstream& stream()
    {
        return out_;
    }

    void clear()
    {
        out_.str("");
    }

private:
    std::ostream& org_;
    std::streambuf* sbf_;
    std::ostringstream out_;
};

inline std::string short_file(const char* file)
{
    auto f = std::string_view{file};
    auto index = f.rfind("/");
    if (index == std::string::npos)
    {
        index = f.rfind("\\");
    }
    if (index == std::string::npos)
    {
        return std::string{f};
    }
    return std::string{f.substr(index + 1)};
}

#define ACTION(x) x

#define LOG_TEST(fn, lvl, msg, prs)                                                 \
    {                                                                               \
        auto rd = Redirect{std::cout};                                              \
        const auto file = short_file(__FILE__);                                     \
        const int line = __LINE__; fn;                                              \
        std::ostringstream oss;                                                     \
        oss << lvl << " | ";                                                        \
        if (prs) CHECK_EQ(rd.stream().str().find(oss.str(), 0), 0);                 \
        else     CHECK_NE(rd.stream().str().find(oss.str(), 0), 0);                 \
        oss.str("");                                                                \
        oss << " | " << msg << " --- " << file << ":" << line;                      \
        if (prs) CHECK_NE(rd.stream().str().find(oss.str(), 0), std::string::npos); \
        else     CHECK_EQ(rd.stream().str().find(oss.str(), 0), std::string::npos); \
    }

TEST_CASE("Log (stdout)")
{
    cmn::log::MIN_LEVEL = LVL_TRACE;

    LOG_TEST(ACTION( TRACE_("hello trace") ), "TRACE", "hello trace", true)
    LOG_TEST(ACTION( DEBUG_("hello debug") ), "DEBUG", "hello debug", true)
    LOG_TEST(ACTION( INFO_("hello info")   ), " INFO", "hello info",  true)
    LOG_TEST(ACTION( WARN_("hello warn")   ), " WARN", "hello warn",  true)
    LOG_TEST(ACTION( ERROR_("hello error") ), "ERROR", "hello error", true)
    LOG_TEST(ACTION( FATAL_("hello fatal") ), "FATAL", "hello fatal", true)

    cmn::log::MIN_LEVEL = LVL_INFO;

    LOG_TEST(ACTION( TRACE_("nope") ), "TRACE", "nope", false)
    LOG_TEST(ACTION( DEBUG_("nope") ), "DEBUG", "nope", false)
    LOG_TEST(ACTION( INFO_("yep")   ), " INFO", "yep",  true)
}
