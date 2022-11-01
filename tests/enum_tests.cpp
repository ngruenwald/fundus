#include "doctest.h"

#include "common/enum.hpp"


// helper for raw pointer strings
#define CHECK_EQ_CSTR(left, right) CHECK_EQ(std::string{left}, std::string{right})


TEST_SUITE("enum")
{
    TEST_CASE("ENUM::from_string") {}
    TEST_CASE("ENUM::to_string") {}
    TEST_CASE("ENUM::from_stream") {}
    TEST_CASE("ENUM::to_stream") {}
    TEST_CASE("ENUM::from_string tpl") {}
    TEST_CASE("ENUMs::from_string") {}
    TEST_CASE("ENUMs::to_string") {}
}


TEST_SUITE_BEGIN("utils");


ENUM(Foo1, bar1, bar2, bar3);

TEST_CASE("ENUM::from_string")
{
    Foo1 foo;  // NOTE: value is undefined!
    bool res;

    from_string("bar1", foo);
    CHECK_EQ(foo, Foo1::bar1);

    from_string("bar2", foo);
    CHECK_EQ(foo, Foo1::bar2);

    from_string("bar3", foo);
    CHECK_EQ(foo, Foo1::bar3);

    res = from_string("bar4", foo);
    CHECK_EQ(res, false);
    CHECK_EQ(foo, Foo1::__unknown__);

    res = from_string("__unknown__", foo);
    CHECK_EQ(res, false);
    CHECK_EQ(foo, Foo1::__unknown__);
}

TEST_CASE("ENUM::to_string")
{
    CHECK_EQ_CSTR(to_string(Foo1::bar1), "bar1");
    CHECK_EQ_CSTR(to_string(Foo1::bar2), "bar2");
    CHECK_EQ_CSTR(to_string(Foo1::bar3), "bar3");

    CHECK_EQ_CSTR(to_string(Foo1::__unknown__), "__unknown__");
}

TEST_CASE("ENUM::from_stream")
{
    std::istringstream iss{"bar2"};

    Foo1 foo;
    iss >> foo;

    CHECK_EQ(foo, Foo1::bar2);
}

TEST_CASE("ENUM::to_stream")
{
    std::ostringstream oss;

    Foo1 foo{Foo1::bar3};
    oss << foo;

    CHECK_EQ(oss.str(), "bar3");
}

TEST_CASE("ENUM::from_string tpl")
{
    auto foo = cmn::enums::from_string<Foo1>("bar3");

    CHECK_EQ(foo, Foo1::bar3);
}


ENUMs(Foo2, ENUMARGS(bar1, bar2, bar3), ENUMARGS(Bar1, Bar2, Bar3));

TEST_CASE("ENUMs::from_string")
{
    Foo2 foo;
    bool res;

    from_string("Bar1", foo);
    CHECK_EQ(foo, Foo2::bar1);

    from_string("Bar2", foo);
    CHECK_EQ(foo, Foo2::bar2);

    from_string("Bar3", foo);
    CHECK_EQ(foo, Foo2::bar3);

    res = from_string("Bar4", foo);
    CHECK_EQ(res, false);
    CHECK_EQ(foo, Foo2::__unknown__);

    res = from_string("__unknown__", foo);
    CHECK_EQ(res, false);
    CHECK_EQ(foo, Foo2::__unknown__);
}

TEST_CASE("ENUMs::to_string")
{
    CHECK_EQ_CSTR(to_string(Foo2::bar1), "Bar1");
    CHECK_EQ_CSTR(to_string(Foo2::bar2), "Bar2");
    CHECK_EQ_CSTR(to_string(Foo2::bar3), "Bar3");

    CHECK_EQ_CSTR(to_string(Foo2::__unknown__), "__unknown__");
}


TEST_SUITE_END();
