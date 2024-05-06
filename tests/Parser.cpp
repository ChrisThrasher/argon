#include <catch2/catch_test_macros.hpp>

import argon;

TEST_CASE("argon::Parser")
{
    SECTION("Type traits")
    {
        STATIC_CHECK(std::is_copy_constructible_v<argon::Parser>);
        STATIC_CHECK(std::is_copy_assignable_v<argon::Parser>);
        STATIC_CHECK(std::is_nothrow_move_constructible_v<argon::Parser>);
        STATIC_CHECK(std::is_nothrow_move_assignable_v<argon::Parser>);
    }

    SECTION("Add option")
    {
        constexpr int argc = 12;
        constexpr const char* argv[argc] = { "example", "-d",  "--verbose", "-f",   "/dev/ttyUSB0", "--unmatched-flag",
                                             "-c",      "100", "--temp",    "98.6", "--speed",      "133.7" };

        bool debug = false;
        bool verbose = false;
        bool not_found = false;
        std::string filename;
        int count = 0;
        double speed = 0.0;

        argon::Parser parser(argc, argv);
        parser.add_option("d", "Debug output", debug);
        parser.add_option("verbose,V", "Verbose output", verbose);
        parser.add_option("not_found", "Flag not found", not_found);
        parser.add_option("f", "Filename", filename);
        parser.add_option("count,c", "Count", count);
        parser.add_option("speed", "Speed", speed);
        parser.parse();

        CHECK(debug);
        CHECK(verbose);
        CHECK_FALSE(not_found);
        CHECK("/dev/ttyUSB0" == filename);
        CHECK(100 == count);
        CHECK(133.7 == speed);
        CHECK(std::vector<std::string_view>({ "--unmatched-flag", "--temp", "98.6" }) == parser.args());
    }

    SECTION("Add position")
    {
        constexpr int argc = 2;
        constexpr const char* argv[argc] = { "example", "config.txt" };

        argon::Parser parser(argc, argv);
        parser.add_position("config_file", "Configuration file");
        parser.parse();

        CHECK("config.txt" == parser.get_position(0));
        CHECK_THROWS_AS(parser.get_position(1), std::out_of_range);
    }

    SECTION("Missing positional argument")
    {
        constexpr int argc = 1;
        constexpr const char* argv[argc] = { "example" };

        argon::Parser parser(argc, argv);
        parser.add_position("config_file", "Configuration file");

        CHECK_THROWS_AS(parser.parse(), std::runtime_error);
    }

    SECTION("Parse zero arguments")
    {
        constexpr int argc = 1;
        constexpr const char* argv[argc] = { "my_program_name" };
        CHECK(std::vector<std::string_view>({}) == argon::Parser(argc, argv).args());
    }

    SECTION("Parse one argument")
    {
        constexpr int argc = 2;
        constexpr const char* argv[argc] = { "my_program_name", "some_input" };
        CHECK(std::vector<std::string_view>({ "some_input" }) == argon::Parser(argc, argv).args());
    }

    SECTION("Parse multiple arguments")
    {
        constexpr int argc = 4;
        constexpr const char* argv[argc] = { "my_program_name", "some_input", "abc", "123" };
        CHECK(std::vector<std::string_view>({ "some_input", "abc", "123" }) == argon::Parser(argc, argv).args());
    }
}
