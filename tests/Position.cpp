#include <argon/Position.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("argon::Position")
{
    SECTION("Type traits")
    {
        STATIC_CHECK(std::is_copy_constructible_v<argon::Position>);
        STATIC_CHECK(std::is_copy_assignable_v<argon::Position>);
        STATIC_CHECK(std::is_nothrow_move_constructible_v<argon::Position>);
        STATIC_CHECK(std::is_nothrow_move_assignable_v<argon::Position>);
    }

    SECTION("Construction")
    {
        const argon::Position position("", "");
        CHECK(position.format() == "\n                          ");
        CHECK(position.name().empty());
    }
}
