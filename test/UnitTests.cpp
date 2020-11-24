#include <Options/Parser.h>

#include <gtest/gtest.h>

TEST(Help, Alias)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-h"};

    opts::Parser parser(argc, argv, "my help text");
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "");
}

TEST(Help, Flag)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--help"};

    opts::Parser parser(argc, argv, "my help text");
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "");
}

TEST(Add, ExitAlias)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-v"};

    opts::Parser parser(argc, argv);
    parser.Add("v", "Print program version", opts::Exit("v0.0.0"));
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "");
}

TEST(Add, ExitFlag)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--version"};

    opts::Parser parser(argc, argv);
    parser.Add("version", "Print program version", opts::Exit("v0.0.0"));
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "");
}

TEST(Add, BoolAlias)
{
    constexpr int argc = 3;
    constexpr const char* argv[argc] = {"example", "--unmatched-flag", "-d"};

    bool debug = false;
    opts::Parser parser(argc, argv);
    parser.Add("d", "Debug output", opts::Bool(debug));
    parser.Parse();
    EXPECT_TRUE(debug);
}

TEST(Add, BoolFlag)
{
    constexpr int argc = 3;
    constexpr const char* argv[argc] = {"example", "--unmatched-flag", "--debug"};

    bool debug = false;
    opts::Parser parser(argc, argv);
    parser.Add("debug", "Debug output", opts::Bool(debug));
    parser.Parse();
    EXPECT_TRUE(debug);
}

TEST(Args, NoArguments)
{
    constexpr int argc = 1;
    constexpr const char* argv[argc] = {"my_program_name"};
    EXPECT_EQ(std::vector<std::string>({}), opts::Parser(argc, argv).Args());
}

TEST(Args, OneArgument)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"my_program_name", "some_input"};
    EXPECT_EQ(std::vector<std::string>({"some_input"}), opts::Parser(argc, argv).Args());
}

TEST(Args, MultipleArgument)
{
    constexpr int argc = 4;
    constexpr const char* argv[argc] = {"my_program_name", "some_input", "abc", "123"};
    EXPECT_EQ(std::vector<std::string>({"some_input", "abc", "123"}), opts::Parser(argc, argv).Args());
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
