#pragma once

#include <Options/Format.h>
#include <Options/Types.h>

#include <iostream>

class Options
{
    void Find(const ExitOption&) const;
    auto MakeOptionList() const -> std::string;

    const std::vector<std::string> m_args{};

    std::vector<ExitOption> m_exit_opts{};

public:
    Options(const int, const char* const[]);
    void Help(const std::string&);
    void Version(const std::string&);
    void Parse() const;
    auto Args() const -> std::vector<std::string>;
};

Options::Options(const int argc, const char* const argv[])
    : m_args(std::vector<std::string>(argv, argv + argc))
{
}

void Options::Help(const std::string& help)
{
    m_exit_opts.push_back(
        {{"-h", "--help"}, "Show this help text", [help, this]() { return help + this->MakeOptionList(); }});
}

void Options::Version(const std::string& version)
{
    m_exit_opts.push_back({{"-v", "--version"}, "Print program version", [version]() { return version; }});
}

void Options::Parse() const
{
    for (const auto& exit_opt : m_exit_opts)
        Find(exit_opt);
}

auto Options::Args() const -> std::vector<std::string>
{
    return std::vector<std::string>(m_args.begin() + 1, m_args.end());
}

void Options::Find(const ExitOption& option) const
{
    if (m_args.size() == 1)
        return;

    for (const auto& flag : option.flags)
    {
        if (m_args[1] == flag)
        {
            std::cout << option.output() << '\n';
            std::exit(0);
        }
    }
}

auto Options::MakeOptionList() const -> std::string
{
    std::string option_list = "\n\nOptions";
    for (const auto& exit_opt : m_exit_opts)
        option_list += FormatOption(exit_opt);

    return option_list;
}
