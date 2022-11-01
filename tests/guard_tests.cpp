#include "doctest.h"

#include "common/guard.hpp"


TEST_CASE("Guard")
{
    bool res{false};

    {
        auto guard = cmn::Guard{[&res]() { res = true; }};
    }

    CHECK_EQ(res, true);
}
