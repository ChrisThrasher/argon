#include <Options.h>

int main(int argc, char* argv[])
{
    Options options;
    options.RegisterExitItem({{"-h", "--help"}, "this is my help text"});
    options.RegisterExitItem({{"-v", "--version"}, "v0.0.0"});
    options.Parse(argc, argv);
}