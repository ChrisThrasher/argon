#include <argon/Parser.h>

#include <iostream>

int main(int argc, char* argv[])
try {
    bool debug;
    int count = 0;
    double speed = 0.0;
    std::string output;

    argon::Parser parser(argc, argv);
    parser.add_option("h,help", "Show this help text", argon::USAGE, "Argon CLI parser example program");
    parser.add_option("version", "Print program version", argon::PRINT, "v0.0.0");
    parser.add_option(debug, "d,debug", "Debug output");
    parser.add_option(count, "c,count", "Number of instances");
    parser.add_option(speed, "speed", "Initial speed");
    parser.add_option(output, "o,output", "Output filename");
    parser.add_position("filename", "Input file");
    parser.parse();

    const auto filename = parser.get_position(0);
} catch (const std::exception& ex) {
    std::cerr << ex.what() << '\n';
    return -1;
}
