#include "doctest.h"

#include <string>

#include "common/result.hpp"


TEST_CASE("Result")
{
    cmn::Result<int, std::string> okResult{42};
    REQUIRE_EQ(okResult.is_ok(), true);
    CHECK_EQ(okResult.value(), 42);

    cmn::Result<int, std::string> errResult{"unknown error"};
    REQUIRE_EQ(errResult.is_ok(), false);
    CHECK_EQ(errResult.error(), "unknown error");
}

TEST_CASE("Result forward ok")
{
    cmn::Result<int, std::string> result{40};

    auto finalResult = result
        .then([](const auto& val) { return val / 2; })
        .then([](const auto& val) { return val / 2; })
        ;

    REQUIRE_EQ(finalResult.is_ok(), true);
    CHECK_EQ(finalResult.value(), 10);
}

TEST_CASE("Result forward error")
{
    cmn::Result<int, std::string> result{40};

    auto finalResult = result
        .then([](const auto& val) { return val / 2; })
        .then([](const auto& val) { return std::string{"oh no"}; })
        ;

    REQUIRE_EQ(finalResult.is_ok(), false);
    CHECK_EQ(finalResult.error(), "oh no");
}

TEST_CASE("Result forward error recovered")
{
    cmn::Result<int, std::string> result{40};

    auto finalResult = result
        .then([](const auto& val) { return val / 2; })
        .then([](const auto& val) { return std::string{"oh no"}; })
        .on_error([](const auto& err) { return 0; })
        .then([](const auto& val) { return val + 1; })
        ;

    REQUIRE_EQ(finalResult.is_ok(), true);
    CHECK_EQ(finalResult.value(), 1);
}

TEST_CASE("Result bad access")
{
    cmn::Result<int, std::string> okResult{0};
    CHECK_THROWS_AS(okResult.error(), cmn::BadResultAccess);

    cmn::Result<int, std::string> errResult{"error"};
    CHECK_THROWS_AS(errResult.value(), cmn::BadResultAccess);
}
