#include <Options/Parser.h>

constexpr auto help = R"(Usage
  example [options])";

int main(int argc, char* argv[])
{
    bool debug = false;
    bool verbose = false;
    int count = 0;
    float temp = 0.0f;
    double speed = 0.0;
    std::string filename = "/file/not/specificed";

    opts::Parser parser(argc, argv, help);
    parser.Add("version", "Print program version", opts::Print("v0.0.0"));
    parser.Add("d,debug", "Debug output", opts::Find(debug));
    parser.Add("v,verbose", "Verbose output", opts::Find(verbose));
    parser.Add("c,count", "Number of instances", opts::Get(count));
    parser.Add("temp", "Initial temperature", opts::Get(temp));
    parser.Add("speed", "Initial speed", opts::Get(speed));
    parser.Add("i,input", "Input filename", opts::Get(filename));
    parser.Parse();

    if (debug)
        std::cout << "Found debug flag\n";
    if (verbose)
        std::cout << "Found verbose flag\n";
    std::cout << "Count: " << count << '\n';
    std::cout << "Temp: " << temp << '\n';
    std::cout << "Speed: " << speed << '\n';
    std::cout << "Filename: " << filename << '\n';
}
