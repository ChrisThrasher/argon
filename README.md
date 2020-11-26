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
    std::string filename = "/file/not/specificed";

    opts::Parser parser(argc, argv, help);
    parser.Add("version", "Print program version", opts::Print("v0.0.0"));
    parser.Add("d,debug", "Debug output", opts::Find(debug));
    parser.Add("v,verbose", "Verbose output", opts::Find(verbose));
    parser.Add("c,count", "Number of instances", opts::Get(count));
    parser.Add("i,input", "Input filename", opts::Get(filename));
    parser.Parse();

    if (debug)
        std::cout << "Found debug flag\n";
    if (verbose)
        std::cout << "Found verbose flag\n";
    std::cout << "Count: " << count << '\n';
    std::cout << "Filename: " << filename << '\n';
}
```

Create an instance of `opts::Parser`. Use `Add` to add as many options as you want. The first argument is a comma-delimited string of flags and aliases. The second is the decription which appears in the help output. The last is a callback. `opts::Print` is helper function providing a callback that prints the provided string before exiting the program. `opts::Find` will set a boolean value `true` if that flag is found. `opts::Get` will retrieve either a string or integer provided immediately after this flag is found.

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
