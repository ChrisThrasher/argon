#pragma once

#include <Options/Option.h>

#include <memory>

namespace opts
{

auto Exit(const std::string& output) -> std::function<void()>
{
    return [output]() {
        std::cout << output << std::endl;
        std::exit(0);
    };
}

auto Bool(bool& exists) -> std::function<void()>
{
    exists = false;
    return [&exists]() { exists = true; };
}

auto String(std::string& str) -> std::function<void(std::string)>
{
    return [&str](std::string value) { str = value; };
}

class Parser
{
    auto MakeOptionList() const -> std::string;

    const std::vector<std::string> m_args{};

    std::vector<std::shared_ptr<opts::Option>> m_options{};

public:
    Parser(const int, const char* const[]);
    Parser(const int, const char* const[], const std::string&);
    void Add(const std::string&, const std::string&, const std::function<void()>&);
    void Add(const std::string&, const std::string&, const std::function<void(std::string)>&);
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
    m_options.push_back(std::make_shared<opts::BasicOption>("help,h", "Show this help text", [help, this]() {
        std::cout << help << this->MakeOptionList();
        std::exit(0);
    }));
}

void Parser::Add(const std::string& flags, const std::string& description, const std::function<void()>& callback)
{
    m_options.push_back(std::make_shared<opts::BasicOption>(flags, description, callback));
}

void Parser::Add(const std::string& flags,
                 const std::string& description,
                 const std::function<void(std::string)>& callback)
{
    m_options.push_back(std::make_shared<opts::ValueOption>(flags, description, callback));
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

    return option_list + '\n';
}

} // namespace opts
