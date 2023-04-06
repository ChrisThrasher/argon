#include <argon/Option.hpp>

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

TEST_CASE("argon::Argument")
{
    SECTION("Type traits")
    {
        STATIC_CHECK(!std::is_copy_constructible_v<argon::Argument>);
        STATIC_CHECK(std::is_copy_assignable_v<argon::Argument>);
        STATIC_CHECK(!std::is_nothrow_move_constructible_v<argon::Argument>);
        STATIC_CHECK(std::is_nothrow_move_assignable_v<argon::Argument>);
    }
}
