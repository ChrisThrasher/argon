# options

This library offers a command line option parser which can detect various types of flags.

# Usage

```cpp
#include <Options/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    bool debug = false;
    bool verbose = false;
    int count = 0;
    double speed = 0.0;
    std::string filename = "";

    opts::Parser parser(argc, argv);
    parser.Add("h,help", "Show this help text", opts::Usage(help));
    parser.Add("version", "Print program version", opts::Print("v0.0.0"));
    parser.Add("d,debug", "Debug output", opts::Find(debug));
    parser.Add("v,verbose", "Verbose output", opts::Find(verbose));
    parser.Add("c,count", "Number of instances", opts::Get(count));
    parser.Add("speed", "Initial speed", opts::Get(speed));
    parser.Add("i,input", "Input filename", opts::Get(filename));
    parser.Parse();
}
```

Create an instance of `opts::Parser`. Use `Add` to add as many options as you want. The first argument is a comma-delimited string of flags and aliases. The second is the decription which appears in the help output. The last is a callback. `opts::Usage` is used for help text. It prints a list of all options after the provided usage information. `opts::Print` is helper function providing a callback that prints the provided string before exiting the program. `opts::Find` will set a boolean value `true` if that flag is found. `opts::Get` will retrieve either a string, integer, float, or double provided immediately after this flag is found.

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
