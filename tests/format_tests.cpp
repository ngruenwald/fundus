#include "doctest.h"

#include "common/format.hpp"


TEST_CASE("Format")
{
    std::string str = cmn::Format{} << "Hello " << "World " << 3;
    CHECK_EQ(str, "Hello World 3");
}
