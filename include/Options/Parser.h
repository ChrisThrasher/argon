#pragma once

#include <Options/Types.h>

#include <iostream>

namespace opts
{

class Parser
{
    auto MakeOptionList() const -> std::string;

    const std::vector<std::string> m_args{};

    std::vector<opts::ExitOption> m_exit_opts{};
    std::vector<opts::BoolOption> m_bool_opts{};

public:
    Parser(const int, const char* const[]);
    Parser(const int, const char* const[], const std::string&);
    void AddExitOption(const std::string&, const char, const std::string&, const std::string&);
    void AddBoolOption(const std::string&, const char, const std::string&, bool&);
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
        {"help", 'h', "Show this help text", [help, this]() { return help + this->MakeOptionList(); }});
}

void Parser::AddExitOption(const std::string& flag,
                           const char alias,
                           const std::string& description,
                           const std::string& output)
{
    m_exit_opts.push_back({flag, alias, description, [output]() { return output; }});
}

void Parser::AddBoolOption(const std::string& flag, const char alias, const std::string& description, bool& value)
{
    m_bool_opts.push_back({flag, alias, description, [&value]() mutable { value = true; }});
}

void Parser::Parse() const
{
    for (const auto& exit_opt : m_exit_opts)
        exit_opt.Find(m_args);
    for (const auto& bool_opt : m_bool_opts)
        bool_opt.Find(m_args);
}

auto Parser::Args() const -> std::vector<std::string>
{
    return std::vector<std::string>(m_args.begin() + 1, m_args.end());
}

auto Parser::MakeOptionList() const -> std::string
{
    std::string option_list = "\n\nOptions";
    for (const auto& exit_opt : m_exit_opts)
        option_list += exit_opt.Format();
    for (const auto& bool_opt : m_bool_opts)
        option_list += bool_opt.Format();

    return option_list;
}

} // namespace opts
