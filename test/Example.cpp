#include <Options/Options.h>

int main(int argc, char* argv[])
{
    Options options(argc, argv);
    options.Help("Usage\n  example [options]");
    options.Version("v0.0.0");
    options.Parse();
}
