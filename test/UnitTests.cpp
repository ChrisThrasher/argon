#include <Options/Options.h>

#include <gtest/gtest.h>

TEST(Help, Short)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-h"};

    EXPECT_EXIT(Options(argc, argv).Help("my help text"), testing::ExitedWithCode(0), "");
}

TEST(Help, Long)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--help"};

    EXPECT_EXIT(Options(argc, argv).Help("my help text"), testing::ExitedWithCode(0), "");
}

TEST(Version, Short)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-v"};

    EXPECT_EXIT(Options(argc, argv).Version("v0.0.0"), testing::ExitedWithCode(0), "");
}

TEST(Version, Long)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--version"};

    EXPECT_EXIT(Options(argc, argv).Version("v0.0.0"), testing::ExitedWithCode(0), "");
}

TEST(ExitItem, Checkout)
{
    constexpr int argc = 3;
    constexpr const char* argv[argc] = {"options", "--flag", "-v"};
    const Options options(argc, argv);

    EXPECT_EXIT(options.ExitItem({"--flag"}, ""), testing::ExitedWithCode(0), "");
    options.ExitItem({"-v"}, "this won't be detected");
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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}