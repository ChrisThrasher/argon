#pragma once

#include <Options/Format.h>
#include <Options/Types.h>

#include <iostream>

namespace opts
{

class Parser
{
    void Find(const opts::ExitOption&) const;
    auto MakeOptionList() const -> std::string;

    const std::vector<std::string> m_args{};

    std::vector<opts::ExitOption> m_exit_opts{};

public:
    Parser(const int, const char* const[]);
    Parser(const int, const char* const[], const std::string&);
    void AddExitOption(const std::vector<std::string>&, const std::string&, const std::string&);
    void Parse() const;
    auto Args() const -> std::vector<std::string>;
};

Parser::Parser(const int argc, const char* const argv[])
    : m_args(std::vector<std::string>(argv, argv + argc))
{
}

Parser::Parser(const int argc, const char* const argv[], const std::string& help)
    : Parser(argc, argv)
{
    m_exit_opts.push_back(
        {{"h", "help"}, "Show this help text", [help, this]() { return help + this->MakeOptionList(); }});
}

void Parser::AddExitOption(const std::vector<std::string>& flags,
                           const std::string& description,
                           const std::string& output)
{
    m_exit_opts.push_back({flags, description, [output]() { return output; }});
}

void Parser::Parse() const
{
    for (const auto& exit_opt : m_exit_opts)
        Find(exit_opt);
}

auto Parser::Args() const -> std::vector<std::string>
{
    return std::vector<std::string>(m_args.begin() + 1, m_args.end());
}

void Parser::Find(const opts::ExitOption& option) const
{
    if (m_args.size() == 1)
        return;

    for (const auto& flag : option.Flags())
    {
        if (m_args[1] == flag)
        {
            std::cout << option.Output() << '\n';
            std::exit(0);
        }
    }
}

auto Parser::MakeOptionList() const -> std::string
{
    std::string option_list = "\n\nOptions";
    for (const auto& exit_opt : m_exit_opts)
        option_list += FormatOption(exit_opt);

    return option_list;
}

} // namespace opts
