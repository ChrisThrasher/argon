#include <argon/Parser.hpp>

#include <catch2/catch_session.hpp>

int main(int argc, char* argv[])
{
    bool debug = false;
    int count = 0;
    double speed = 0.0;
    std::string output;

    argon::Parser parser(argc, argv);
    parser.add_option("h,help", "Show this help text", argon::USAGE, "Argon CLI parser test program");
    parser.add_option("version", "Print program version", argon::PRINT, "v0.0.0");
    parser.add_option("d,debug", "Debug output", debug);
    parser.add_option("c,count", "Number of instances", count);
    parser.add_option("speed", "Initial speed", speed);
    parser.add_option("o,output", "Output filename", output);
    parser.add_position("filename", "Input file");
    parser.parse();

    return Catch::Session().run(argc, argv);
}
