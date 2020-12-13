#include <argon/Parser.h>

constexpr auto help = R"(Usage
  example <filename> [options])";

int main(int argc, char* argv[])
{
    bool debug = false;
    int count = 0;
    double speed = 0.0;
    std::string output = "";

    argon::Parser parser(argc, argv);
    parser.Add("h,help", "Show this help text", argon::Usage(help));
    parser.Add("version", "Print program version", argon::Print("v0.0.0"));
    parser.Add("d,debug", "Debug output", argon::Find(debug));
    parser.Add("c,count", "Number of instances", argon::Get(count));
    parser.Add("speed", "Initial speed", argon::Get(speed));
    parser.Add("o,output", "Output filename", argon::Get(output));
    parser.Add("filename", "Input file");
    parser.Parse();

    const auto filename = parser.Args().at(0);
}
