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
    parser.AddExitOption("version", 'v', "Print program version", "v0.0.0");
    parser.AddBoolOption("debug", 'd', "Debug output", debug);
    parser.Parse();

    if (debug)
        std::cout << "Found debug flag\n";
}
```

Create an instance of `opts::Parser`. Use any combination of `AddExitOption` and `AddBoolOption` to detect various types of flags.

To supply a help text that automatically appends all options, use the 3-argument constructor and seen above. Here's what the formatting help output looks like:

```
$ example --help
Usage
  example [options]

Options
  -h, --help      Show this help text
  -v, --version   Print program version
  -d, --debug     Debug output
```
