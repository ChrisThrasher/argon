#include <argon/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    bool debug = false;
    bool verbose = false;
    int count = 0;
    double speed = 0.0;
    std::string filename = "";

    argon::Parser parser(argc, argv);
    parser.Add("h,help", "Show this help text", argon::Usage(help));
    parser.Add("version", "Print program version", argon::Print("v0.0.0"));
    parser.Add("d,debug", "Debug output", argon::Find(debug));
    parser.Add("v,verbose", "Verbose output", argon::Find(verbose));
    parser.Add("c,count", "Number of instances", argon::Get(count));
    parser.Add("speed", "Initial speed", argon::Get(speed));
    parser.Add("i,input", "Input filename", argon::Get(filename));
    parser.Parse();
}
