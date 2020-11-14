#include <Options.h>

int main(int argc, char* argv[])
{
    Options options(argc, argv);
    options.RegisterExitItem({"-h", "--help"}, "this is my help text");
    options.RegisterExitItem({"-v", "--version"}, "v0.0.0");
}