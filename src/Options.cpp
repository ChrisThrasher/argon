#include <Options.h>

int main(int argc, char* argv[])
{
    Options options;
    options.RegisterHelp("heeeeeeelp");
    options.RegisterVersion("v6.9");
    options.Parse(argc, argv);
}