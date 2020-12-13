#include <Options/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    bool debug = false;
    bool verbose = false;
    int count = 0;
    double speed = 0.0;
    std::string filename = "";

    opts::Parser parser(argc, argv);
    parser.Add("h,help", "Show this help text", opts::Usage(help));
    parser.Add("version", "Print program version", opts::Print("v0.0.0"));
    parser.Add("d,debug", "Debug output", opts::Find(debug));
    parser.Add("v,verbose", "Verbose output", opts::Find(verbose));
    parser.Add("c,count", "Number of instances", opts::Get(count));
    parser.Add("speed", "Initial speed", opts::Get(speed));
    parser.Add("i,input", "Input filename", opts::Get(filename));
    parser.Parse();
}
