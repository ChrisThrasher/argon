# options

This library offers a command line parser which can detect various types of flags.

# Usage

```cpp
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
```

Create an instance of `opts::Parser`. Use any combination of `AddExitOption` and `AddBoolOption` to detect various types of flags. Flags themselves are defined as a comma-delimited string where each item is another flag or alias. You can add as many flags and aliases as you'd like.

To supply a help text that automatically appends all options, use the 3-argument constructor as seen above. Here's what that looks like.

```
$ example --help
Usage
  example [options]

Options
  -h, --help      Show this help text
  -v, --version   Print program version
  -d, --debug     Debug output
```
