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
    float temp = 0.0f;
    double speed = 0.0;
    std::string filename = "/file/not/specificed";

    opts::Parser parser(argc, argv, help);
    parser.Add("version", "Print program version", opts::Print("v0.0.0"));
    parser.Add("d,debug", "Debug output", opts::Find(debug));
    parser.Add("v,verbose", "Verbose output", opts::Find(verbose));
    parser.Add("c,count", "Number of instances", opts::Get(count));
    parser.Add("temp", "Initial temperature", opts::Get(temp));
    parser.Add("speed", "Initial speed", opts::Get(speed));
    parser.Add("i,input", "Input filename", opts::Get(filename));
    parser.Parse();
}
```

Create an instance of `opts::Parser`. Use `Add` to add as many options as you want. The first argument is a comma-delimited string of flags and aliases. The second is the decription which appears in the help output. The last is a callback. `opts::Print` is helper function providing a callback that prints the provided string before exiting the program. `opts::Find` will set a boolean value `true` if that flag is found. `opts::Get` will retrieve either a string, integer, float, or double provided immediately after this flag is found.

To supply a help text that automatically appends all options, use the 3-argument constructor as seen above. Here's what that looks like.

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
  -i, --input     Input filename
```
