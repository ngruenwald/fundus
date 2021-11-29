#pragma once

#include <string_view>
#include <vector>

namespace cmn {

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

} // namespace cmn
