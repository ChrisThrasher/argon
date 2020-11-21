#include <Options/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    opts::Parser parser(argc, argv, help);
    parser.Version("v0.0.0");
    parser.Parse();
}
