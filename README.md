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
    parser.AddOption("h,help", "Show this help text", argon::USAGE, help);
    parser.AddOption("version", "Print program version", argon::PRINT, "v0.0.0");
    parser.AddOption(debug, "d,debug", "Debug output");
    parser.AddOption(count, "c,count", "Number of instances");
    parser.AddOption(speed, "speed", "Initial speed");
    parser.AddOption(output, "o,output", "Output filename");
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

Create an instance of `argon::Parser`. Use `AddOption` to add as many options as you want. The first argument is a comma-delimited string of flags and aliases. The second is the decription which appears in the help output. The 3rd argument is either a string constant which gets printed to the console or its a mutable references that gets modified according to what the parser detects. If a string constant is a provided, a fourth argument is an enum  where `argon::USAGE` indicates that a usage text is printed after the provided string whereas `argon::PRINT` simply prints the provided string. 

Here's what the formatted usage information looks like:

```
$ example --help
Usage
  example <filename> [options]

Positions
  filename                Input file

Options
  -h, --help              Show this help text
  --version               Print program version
  -d, --debug             Debug output
  -c, --count <value>     Number of instances
  --speed <value>         Initial speed
  -o, --output <value>    Output filename
```
