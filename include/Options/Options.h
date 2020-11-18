#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct TerminalOption
{
    std::vector<std::string> flags;
    std::string description;
    std::string output;
};

class Options
{
    const std::vector<std::string> args{};

    TerminalOption help;
    TerminalOption version;

    bool ExitItem(const TerminalOption&) const;
    auto MakeOptionList() const -> std::string;

public:
    Options(const int, const char* const[]);
    void Help(const std::string&);
    void Version(const std::string&);
    void Parse() const;
    auto At(const int, const std::string&) const -> std::string;
    auto Args() const -> std::vector<std::string>;
};

Options::Options(const int argc, const char* const argv[])
    : args(std::vector<std::string>(argv, argv + argc))
{
}

void Options::Help(const std::string& help_text) { help = {{"-h", "--help"}, "Show this help text", help_text}; }

void Options::Version(const std::string& version_text)
{
    version = {{"-v", "--version"}, "Print program version", version_text};
}

void Options::Parse() const
{
    if (ExitItem(version))
    {
        std::cout << version.output << '\n';
        std::exit(0);
    }
    if (ExitItem(help))
    {
        std::cout << help.output << MakeOptionList() << '\n';
        std::exit(0);
    }
}

auto Options::At(const int pos, const std::string& name) const -> std::string
{
    const auto i = static_cast<size_t>(pos);
    if (i < args.size())
        return args[i];
    throw std::out_of_range("Failed to find " + name + " at index " + std::to_string(i));
}

auto Options::Args() const -> std::vector<std::string>
{
    return std::vector<std::string>(args.begin() + 1, args.end());
}

bool Options::ExitItem(const TerminalOption& option) const
{
    if (args.size() == 1)
        return false;

    for (const auto& flag : option.flags)
    {
        if (args[1] == flag)
        {
            return true;
        }
    }
    return false;
}

auto Options::MakeOptionList() const -> std::string
{
    if (help.flags.empty() and version.flags.empty())
        return "";

    std::stringstream description;
    description << "\nOptions";
    if (not help.flags.empty())
    {
        description << "\n  ";
        for (const auto& flag : help.flags)
            description << flag << ' ';
        description << help.description;
    }
    if (not version.flags.empty())
    {
        description << "\n  ";
        for (const auto& flag : version.flags)
            description << flag << ' ';
        description << version.description;
    }
    return description.str();
}