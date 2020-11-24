#include <Options/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    bool debug = false;
    bool verbose = false;

    opts::Parser parser(argc, argv, help);
    parser.Add("version", "Print program version", opts::Exit("v0.0.0"));
    parser.Add("d,debug", "Debug output", opts::Bool(debug));
    parser.Add("v,verbose", "Verbose output", opts::Bool(verbose));
    parser.Parse();

    if (debug)
        std::cout << "Found debug flag\n";
    if (verbose)
        std::cout << "Found verbose flag\n";
}
