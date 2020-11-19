#pragma once

#include <Options/Format.h>
#include <Options/Types.h>

#include <iostream>

class Options
{
    void Find(const ExitOption&) const;
    auto MakeOptionList() const -> std::string;

    const std::vector<std::string> args{};

    std::vector<ExitOption> exit_opts{};

public:
    Options(const int, const char* const[]);
    void Help(const std::string&);
    void Version(const std::string&);
    void Parse() const;
    auto Args() const -> std::vector<std::string>;
};

Options::Options(const int argc, const char* const argv[])
    : args(std::vector<std::string>(argv, argv + argc))
{
}

void Options::Help(const std::string& help)
{
    exit_opts.push_back(
        {{"-h", "--help"}, "Show this help text", [help, this]() { return help + this->MakeOptionList(); }});
}

void Options::Version(const std::string& version)
{
    exit_opts.push_back({{"-v", "--version"}, "Print program version", [version]() { return version; }});
}

void Options::Parse() const
{
    for (const auto& exit_opt : exit_opts)
        Find(exit_opt);
}

auto Options::Args() const -> std::vector<std::string>
{
    return std::vector<std::string>(args.begin() + 1, args.end());
}

void Options::Find(const ExitOption& option) const
{
    if (args.size() == 1)
        return;

    for (const auto& flag : option.flags)
    {
        if (args[1] == flag)
        {
            std::cout << option.output() << '\n';
            std::exit(0);
        }
    }
}

auto Options::MakeOptionList() const -> std::string
{
    std::string option_list = "\n\nOptions";
    for (const auto& exit_opt : exit_opts)
        option_list += FormatOption(exit_opt);

    return option_list;
}