#include <argon/Option.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("argon::Option")
{
    SECTION("Type traits")
    {
        STATIC_CHECK(!std::is_copy_constructible_v<argon::Option>);
        STATIC_CHECK(std::is_copy_assignable_v<argon::Option>);
        STATIC_CHECK(!std::is_nothrow_move_constructible_v<argon::Option>);
        STATIC_CHECK(std::is_nothrow_move_assignable_v<argon::Option>);
    }
}

TEST_CASE("argon::BasicOption")
{
    SECTION("Type traits")
    {
        STATIC_CHECK(std::is_copy_constructible_v<argon::BasicOption>);
        STATIC_CHECK(std::is_copy_assignable_v<argon::BasicOption>);
        // STATIC_CHECK(std::is_nothrow_move_constructible_v<argon::BasicOption>);
        STATIC_CHECK(std::is_nothrow_move_assignable_v<argon::BasicOption>);
    }

    SECTION("Construction")
    {
        const argon::BasicOption option("", "", []() {});
        CHECK(option.format() == "\n  --                      ");
    }
}

TEST_CASE("argon::ValueOption")
{
    SECTION("Type traits")
    {
        STATIC_CHECK(std::is_copy_constructible_v<argon::ValueOption>);
        STATIC_CHECK(std::is_copy_assignable_v<argon::ValueOption>);
        // STATIC_CHECK(std::is_nothrow_move_constructible_v<argon::ValueOption>);
        STATIC_CHECK(std::is_nothrow_move_assignable_v<argon::ValueOption>);
    }

    SECTION("Construction")
    {
        const argon::ValueOption option("", "", [](std::string_view) {});
        CHECK(option.format() == "\n  -- <value>              ");
    }
}
