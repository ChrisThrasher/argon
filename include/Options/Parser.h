#pragma once

#include <Options/Option.h>

#include <memory>

namespace opts
{

struct Usage
{
    const std::string help;

    Usage(const std::string& a_help)
        : help(a_help)
    {
    }
};

auto Print(const std::string& output) -> std::function<void()>
{
    return [output]() {
        std::cerr << output << std::endl;
        std::exit(0);
    };
}

auto Find(bool& exists) -> std::function<void()>
{
    exists = false;
    return [&exists]() { exists = true; };
}

auto Get(std::string& str) -> std::function<void(std::string)>
{
    return [&str](std::string value) { str = value; };
}

auto Get(int& i) -> std::function<void(std::string)>
{
    return [&i](std::string value) { i = std::stoi(value); };
}

auto Get(float& f) -> std::function<void(std::string)>
{
    return [&f](std::string value) { f = std::stof(value); };
}

auto Get(double& d) -> std::function<void(std::string)>
{
    return [&d](std::string value) { d = std::stod(value); };
}

class Parser
{
    auto MakeOptionList() const -> std::string;

    const std::vector<std::string> m_args{};

    std::vector<std::shared_ptr<opts::Option>> m_options{};

public:
    Parser(const int, const char* const[]);
    Parser(const int, const char* const[], const std::string&);
    void Add(const std::string&, const std::string&, const Usage&);
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
    Add("h,help", "Show this help text", opts::Usage(help));
}

void Parser::Add(const std::string& flags, const std::string& description, const Usage& usage)
{
    m_options.push_back(std::make_shared<opts::BasicOption>(flags, description, [usage, this]() {
        std::cerr << usage.help << this->MakeOptionList();
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
    std::stringstream option_list;
    option_list << "\n\nOptions";
    for (const auto& option : m_options)
        option_list << option->Format();
    option_list << '\n';

    return option_list.str();
}

} // namespace opts
