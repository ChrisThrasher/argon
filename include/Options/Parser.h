#pragma once

#include <Options/Option.h>

#include <memory>

namespace opts
{

class Parser
{
    auto MakeOptionList() const -> std::string;

    const std::vector<std::string> m_args{};

    std::vector<std::shared_ptr<opts::Option>> m_options{};

public:
    Parser(const int, const char* const[]);
    Parser(const int, const char* const[], const std::string&);
    void Add(const opts::ExitOption& option);
    void AddBoolOption(const std::string&, const char, const std::string&, bool&);
    void Parse() const;
    auto Args() const -> std::vector<std::string>;
};

Parser::Parser(const int argc, const char* const argv[])
    : m_args(std::vector<std::string>(argv + 1, argv + argc))
{
}

Parser::Parser(const int argc, const char* const argv[], const std::string& help)
    : Parser(argc, argv)
{
    m_options.push_back(std::make_shared<opts::ExitOption>(
        "help", 'h', "Show this help text", [help, this]() { return help + this->MakeOptionList(); }));
}

void Parser::Add(const opts::ExitOption& option) { m_options.push_back(std::make_shared<opts::ExitOption>(option)); }

void Parser::AddBoolOption(const std::string& flag, const char alias, const std::string& description, bool& value)
{
    m_options.push_back(std::make_shared<opts::BoolOption>(flag, alias, description, value));
}

void Parser::Parse() const
{
    if (m_args.empty())
        return;

    for (const auto& option : m_options)
        option->Find(m_args);
}

auto Parser::Args() const -> std::vector<std::string> { return m_args; }

auto Parser::MakeOptionList() const -> std::string
{
    std::string option_list = "\n\nOptions";
    for (const auto& option : m_options)
        option_list += option->Format();

    return option_list;
}

} // namespace opts
