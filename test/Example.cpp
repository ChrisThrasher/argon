#include <Options/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    opts::Parser parser(argc, argv, help);
    parser.AddExitOption("version", 'v', "Print program version", "v0.0.0");
    bool debug = false;
    parser.AddBoolOption("debug", 'd', "Debug output", debug);
    parser.Parse();

    if (debug)
        std::cout << "Found debug flag\n";
}
