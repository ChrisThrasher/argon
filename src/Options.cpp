#include <Options.h>

int main(int argc, char* argv[])
{
    Options options(argc, argv);
    options.ExitItem({"-h", "--help"}, "this is my help text");
    options.ExitItem({"-v", "--version"}, "v0.0.0");
    std::cout << options.Int({"-i", "--int"}).value_or(-1) << '\n';
}