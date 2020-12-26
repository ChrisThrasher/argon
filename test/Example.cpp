#include <argon/Parser.h>

constexpr auto help = R"(Usage
  example <filename> [options])";

int main(int argc, char* argv[])
try
{
    bool debug = false;
    int count = 0;
    double speed = 0.0;
    std::string output = "";

    argon::Parser parser(argc, argv);
    parser.AddOption("h,help", "Show this help text", help, argon::PrintUsage::YES);
    parser.AddOption("version", "Print program version", "v0.0.0", argon::PrintUsage::NO);
    parser.AddOption("d,debug", "Debug output", debug);
    parser.AddOption("c,count", "Number of instances", count);
    parser.AddOption("speed", "Initial speed", speed);
    parser.AddOption("o,output", "Output filename", output);
    parser.AddPosition("filename", "Input file");
    parser.Parse();

    const auto filename = parser.GetPosition(0);
}
catch (const std::exception& ex)
{
    std::cerr << ex.what() << '\n';
    return -1;
}
