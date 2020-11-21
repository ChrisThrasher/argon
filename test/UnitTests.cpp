#include <Options/Parser.h>

#include <gtest/gtest.h>

TEST(Help, Short)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-h"};

    opts::Parser parser(argc, argv, "my help text");
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "");
}

TEST(Help, Long)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--help"};

    opts::Parser parser(argc, argv, "my help text");
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "");
}

TEST(AddExitOption, Short)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-v"};

    opts::Parser parser(argc, argv);
    parser.AddExitOption("version", 'v', "Print program version", "v0.0.0");
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "");
}

TEST(AddExitOption, Long)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--version"};

    opts::Parser parser(argc, argv);
    parser.AddExitOption("version", 'v', "Print program version", "v0.0.0");
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "");
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
