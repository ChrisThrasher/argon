#include <argon/Parser.h>

#include <gtest/gtest.h>

TEST(AddOption, Usage)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"example", "-h"};

    argon::Parser parser(argc, argv);
    parser.AddOption("h,help", "Show this help text", argon::Usage("my help text"));
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "my help text");
}

TEST(AddOption, PrintAlias)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"example", "-v"};

    argon::Parser parser(argc, argv);
    parser.AddOption("v", "Print program version", argon::Print("v0.0.0"));
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "v0.0.0");
}

TEST(AddOption, PrintFlag)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"example", "--version"};

    argon::Parser parser(argc, argv);
    parser.AddOption("version", "Print program version", argon::Print("v0.0.0"));
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "v0.0.0");
}

TEST(AddOption, FindOption)
{
    constexpr int argc = 4;
    constexpr const char* argv[argc] = {"example", "--unmatched-flag", "-d", "--verbose"};

    bool debug = false;
    bool verbose = false;
    bool not_found = false;

    argon::Parser parser(argc, argv);
    parser.AddOption("d", "Debug output", argon::Find(debug));
    parser.AddOption("verbose,V", "Verbose output", argon::Find(verbose));
    parser.AddOption("not_found", "Flag not found", argon::Find(not_found));
    parser.Parse();

    EXPECT_TRUE(debug);
    EXPECT_TRUE(verbose);
    EXPECT_FALSE(not_found);
}

TEST(AddOption, Get)
{
    constexpr int argc = 10;
    constexpr const char* argv[argc] = {"example", "-f", "/dev/ttyUSB0", "--unmatched-flag", "-c", "100", "--temp", "98.6", "--speed", "133.7"};

    std::string filename;
    auto count = 0;
    auto speed = 0.0;

    argon::Parser parser(argc, argv);
    parser.AddOption("f", "Filename", argon::Get(filename));
    parser.AddOption("count,c", "Count", argon::Get(count));
    parser.AddOption("speed", "Speed", argon::Get(speed));
    parser.Parse();

    EXPECT_EQ("/dev/ttyUSB0", filename);
    EXPECT_EQ(100, count);
    EXPECT_EQ(133.7, speed);
    EXPECT_EQ(std::vector<std::string>({"--unmatched-flag", "--temp", "98.6"}), parser.Args());
}

TEST(Args, NoArguments)
{
    constexpr int argc = 1;
    constexpr const char* argv[argc] = {"my_program_name"};
    EXPECT_EQ(std::vector<std::string>({}), argon::Parser(argc, argv).Args());
}

TEST(Args, OneArgument)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"my_program_name", "some_input"};
    EXPECT_EQ(std::vector<std::string>({"some_input"}), argon::Parser(argc, argv).Args());
}

TEST(Args, MultipleArgument)
{
    constexpr int argc = 4;
    constexpr const char* argv[argc] = {"my_program_name", "some_input", "abc", "123"};
    EXPECT_EQ(std::vector<std::string>({"some_input", "abc", "123"}), argon::Parser(argc, argv).Args());
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
