#include <sstream>

#include "doctest.h"

#include "common/arguments.hpp"


/*
struct Arguments
{
    int argc;
    char** argv;

    std::vector<std::string_view> args;

    static Arguments from_args(int argc, char** argv)
    {
        auto result = Arguments{.argc=argc, .argv=argv};
        for (int idx = 0; idx < argc; idx++)
        {
            result.args.emplace_back(argv[idx]);
        }
        return result;
    }
};
*/

TEST_CASE("Arguments")
{
    int argc = 2;
    const char* argv[] { "foo", "bar" };

    auto arguments = cmn::Arguments::from_args(argc, const_cast<char**>(argv));

    CHECK_EQ(arguments.args.size(), 2);
    CHECK_EQ(arguments.args[0], "foo");
    CHECK_EQ(arguments.args[1], "bar");
}
