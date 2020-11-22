#include <Options/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    bool debug = false;

    opts::Parser parser(argc, argv, help);
    parser.Add(opts::ExitOption("version", 'v', "Print program version", "v0.0.0"));
    parser.AddBoolOption("debug", 'd', "Debug output", debug);
    parser.Parse();

    if (debug)
        std::cout << "Found debug flag\n";
}
