#pragma once

#include <Options/Format.h>
#include <Options/Types.h>

#include <iostream>

class Options
{
    bool Find(const ExitOption&) const;
    auto MakeOptionList() const -> std::string;

    const std::vector<std::string> args{};

    ExitOption help;
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

void Options::Help(const std::string& help_text) { help = {{"-h", "--help"}, "Show this help text", help_text}; }

void Options::Version(const std::string& version_text)
{
    exit_opts.push_back({{"-v", "--version"}, "Print program version", version_text});
}

void Options::Parse() const
{
    if (Find(help))
    {
        std::cout << help.output << MakeOptionList() << '\n';
        std::exit(0);
    }
    for (const auto& exit_opt : exit_opts)
    {
        std::cout << exit_opt.output << '\n';
        std::exit(0);
    }
}

auto Options::Args() const -> std::vector<std::string>
{
    return std::vector<std::string>(args.begin() + 1, args.end());
}

bool Options::Find(const ExitOption& option) const
{
    if (args.size() == 1)
        return false;

    for (const auto& flag : option.flags)
        if (args[1] == flag)
            return true;

    return false;
}

auto Options::MakeOptionList() const -> std::string
{
    std::string option_list = "\n\nOptions" + FormatOption(help);
    for (const auto& exit_opt : exit_opts)
        option_list += FormatOption(exit_opt);

    return option_list;
}