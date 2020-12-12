#include <Options/Parser.h>

#include <gtest/gtest.h>

TEST(Add, Usage)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-h"};

    opts::Parser parser(argc, argv);
    parser.Add("h,help", "Show this help text", opts::Usage("my help text"));
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "my help text");
}

TEST(Add, PrintAlias)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-v"};

    opts::Parser parser(argc, argv);
    parser.Add("v", "Print program version", opts::Print("v0.0.0"));
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "v0.0.0");
}

TEST(Add, PrintFlag)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--version"};

    opts::Parser parser(argc, argv);
    parser.Add("version", "Print program version", opts::Print("v0.0.0"));
    EXPECT_EXIT(parser.Parse(), testing::ExitedWithCode(0), "v0.0.0");
}

TEST(Add, FindOption)
{
    constexpr int argc = 4;
    constexpr const char* argv[argc] = {"example", "--unmatched-flag", "-d", "--verbose"};

    bool debug = false;
    bool verbose = false;
    bool not_found = false;

    opts::Parser parser(argc, argv);
    parser.Add("d", "Debug output", opts::Find(debug));
    parser.Add("verbose,V", "Verbose output", opts::Find(verbose));
    parser.Add("not_found", "Flag not found", opts::Find(not_found));
    parser.Parse();

    EXPECT_TRUE(debug);
    EXPECT_TRUE(verbose);
    EXPECT_FALSE(not_found);
}

TEST(Add, Get)
{
    constexpr int argc = 10;
    constexpr const char* argv[argc] = {"example", "-f", "/dev/ttyUSB0", "--unmatched-flag", "-c", "100", "--temp", "98.6", "--speed", "133.7"};

    std::string filename;
    auto count = 0;
    auto speed = 0.0;

    opts::Parser parser(argc, argv);
    parser.Add("f", "Filename", opts::Get(filename));
    parser.Add("count,c", "Count", opts::Get(count));
    parser.Add("speed", "Speed", opts::Get(speed));
    parser.Parse();

    EXPECT_EQ("/dev/ttyUSB0", filename);
    EXPECT_EQ(100, count);
    EXPECT_EQ(133.7, speed);
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
