#include <Options/Options.h>

#include <gtest/gtest.h>

TEST(Help, Short)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-h"};

    Options options(argc, argv);
    options.Help("my help text");
    EXPECT_EXIT(options.Parse(), testing::ExitedWithCode(0), "");
}

TEST(Help, Long)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--help"};

    Options options(argc, argv);
    options.Help("my help text");
    EXPECT_EXIT(options.Parse(), testing::ExitedWithCode(0), "");
}

TEST(Version, Short)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-v"};

    Options options(argc, argv);
    options.Version("v0.0.0");
    EXPECT_EXIT(options.Parse(), testing::ExitedWithCode(0), "");
}

TEST(Version, Long)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--version"};

    Options options(argc, argv);
    options.Version("v0.0.0");
    EXPECT_EXIT(options.Parse(), testing::ExitedWithCode(0), "");
}

TEST(At, Checkout)
{
    constexpr int argc = 3;
    constexpr const char* argv[argc] = {"program_name", "first_arg", "second_arg"};
    const Options options(argc, argv);

    EXPECT_EQ("program_name", options.At(0, ""));
    EXPECT_EQ("first_arg", options.At(1, ""));
    EXPECT_EQ("second_arg", options.At(2, ""));
    EXPECT_THROW(options.At(3, ""), std::out_of_range);
}

TEST(Args, NoArguments)
{
    constexpr int argc = 1;
    constexpr const char* argv[argc] = {"my_program_name"};
    EXPECT_EQ(std::vector<std::string>({}), Options(argc, argv).Args());
}

TEST(Args, OneArgument)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"my_program_name", "some_input"};
    EXPECT_EQ(std::vector<std::string>({"some_input"}), Options(argc, argv).Args());
}

TEST(Args, MultipleArgument)
{
    constexpr int argc = 4;
    constexpr const char* argv[argc] = {"my_program_name", "some_input", "abc", "123"};
    EXPECT_EQ(std::vector<std::string>({"some_input", "abc", "123"}), Options(argc, argv).Args());
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
