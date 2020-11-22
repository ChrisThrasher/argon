#include <Options/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    bool debug = false;
    bool verbose = false;

    opts::Parser parser(argc, argv, help);
    parser.Add(opts::ExitOption("version", "Print program version", "v0.0.0"));
    parser.Add(opts::BoolOption("d,debug", "Debug output", debug));
    parser.Add(opts::BoolOption("v,verbose", "Verbose output", verbose));
    parser.Parse();

    if (debug)
        std::cout << "Found debug flag\n";
    if (verbose)
        std::cout << "Found verbose flag\n";
}
