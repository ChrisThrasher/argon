#include <argon/Parser.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Usage action")
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = { "example", "-h" };

    argon::Parser parser(argc, argv);
    parser.add_option("h", "Show this help text", argon::USAGE, "my help text");
    // CHECK_EXIT(parser.parse(), testing::ExitedWithCode(0), "my help text");
}

TEST_CASE("Print action")
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = { "example", "--version" };

    argon::Parser parser(argc, argv);
    parser.add_option("version", "Print program version", argon::PRINT, "v0.0.0");
    // CHECK_EXIT(parser.parse(), testing::ExitedWithCode(0), "v0.0.0");
}

TEST_CASE("Add option")
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

TEST_CASE("Add position")
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = { "example", "config.txt" };

    argon::Parser parser(argc, argv);
    parser.add_position("config_file", "Configuration file");
    parser.parse();

    CHECK("config.txt" == parser.get_position(0));
    CHECK_THROWS_AS(parser.get_position(1), std::out_of_range);
}

TEST_CASE("Missing positional argument")
{
    constexpr int argc = 1;
    constexpr const char* argv[argc] = { "example" };

    argon::Parser parser(argc, argv);
    parser.add_position("config_file", "Configuration file");

    CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Parse zero arguments")
{
    constexpr int argc = 1;
    constexpr const char* argv[argc] = { "my_program_name" };
    CHECK(std::vector<std::string_view>({}) == argon::Parser(argc, argv).args());
}

TEST_CASE("Parse one argument")
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = { "my_program_name", "some_input" };
    CHECK(std::vector<std::string_view>({ "some_input" }) == argon::Parser(argc, argv).args());
}

TEST_CASE("Parse multiple arguments")
{
    constexpr int argc = 4;
    constexpr const char* argv[argc] = { "my_program_name", "some_input", "abc", "123" };
    CHECK(std::vector<std::string_view>({ "some_input", "abc", "123" }) == argon::Parser(argc, argv).args());
}
