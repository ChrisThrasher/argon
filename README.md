# argon

Argon is a command line argument parser which supports optional and positional arguments.

# Usage

```cpp
#include <argon/Parser.h>

constexpr auto help = R"(Usage
  example <filename> [options])";

int main(int argc, char* argv[])
try
{
    bool debug;
    int count = 0;
    double speed = 0.0;
    std::string output;

    argon::Parser parser(argc, argv);
    parser.AddOption("h,help", "Show this help text", help, argon::USAGE);
    parser.AddOption("version", "Print program version", "v0.0.0", argon::PRINT);
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
```

Create an instance of `argon::Parser`. Use `AddOption` to add as many options as you want. The first argument is a comma-delimited string of flags and aliases. The second is the decription which appears in the help output. The last is a callback. `argon::Usage` is used for help text. It prints a list of all options after the provided usage information. `argon::Print` is helper function providing a callback that prints the provided string before exiting the program. `argon::Find` will set a boolean value `true` if that flag is found. `argon::Get` will retrieve either a string, integer, float, or double provided immediately after this flag is found.

Here's what the formatted usage information looks like:

```
$ example --help
Usage
  example [options]

Options
  -h, --help      Show this help text
  --version       Print program version
  -d, --debug     Debug output
  -v, --verbose   Verbose output
  -c, --count     Number of instances
  --speed         Initial speed
  -i, --input     Input filename
```
