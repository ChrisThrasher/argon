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

    opts::Parser parser(argc, argv, help);
    parser.Add(opts::ExitOption("version,v", "Print program version", "v0.0.0"));
    parser.Add(opts::BoolOption("debug,d", "Debug output", debug));
    parser.Parse();

    if (debug)
        std::cout << "Found debug flag\n";
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
