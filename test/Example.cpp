#include <Options/Options.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    opts::Options options(argc, argv, help);
    options.Version("v0.0.0");
    options.Parse();
}
