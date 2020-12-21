#pragma once

#include <argon/Option.h>
#include <argon/Position.h>

#include <map>
#include <memory>

namespace argon
{

class Parser
{
    auto MakeArgumentList() const -> std::string;

    std::vector<std::string> m_args{};

    std::vector<std::shared_ptr<argon::Option>> m_options{};
    std::vector<argon::Position> m_positions{};

public:
    Parser(const int, const char* const[]);
    void AddOption(const std::string&, const std::string&, const std::string&);
    void AddOption(const std::string&, const std::string&, const std::function<void()>&);
    void AddOption(const std::string&, const std::string&, const std::function<void(std::string)>&);
    void AddPosition(const std::string&, const std::string&);
    void Parse();
    auto Args() const -> std::vector<std::string>;
};

Parser::Parser(const int argc, const char* const argv[])
    : m_args(std::vector<std::string>(argv + 1, argv + argc))
{
}

void Parser::AddOption(const std::string& flags, const std::string& description, const std::string& usage)
{
    AddOption(flags, description, [usage, this]() {
        std::cerr << usage << this->MakeArgumentList();
        std::exit(0);
    });
}

void Parser::AddOption(const std::string& flags, const std::string& description, const std::function<void()>& callback)
{
    m_options.push_back(std::make_shared<argon::BasicOption>(flags, description, callback));
}

void Parser::AddOption(const std::string& flags,
                       const std::string& description,
                       const std::function<void(std::string)>& callback)
{
    m_options.push_back(std::make_shared<argon::ValueOption>(flags, description, callback));
}

void Parser::AddPosition(const std::string& name, const std::string& description)
{
    m_positions.push_back(argon::Position(name, description));
}

void Parser::Parse()
{
    for (const auto& option : m_options)
        option->Find(m_args);

    if (m_positions.size() > m_args.size())
        throw std::runtime_error("Expected " + std::to_string(m_positions.size()) + " positional arguments. Received " +
                                 std::to_string(m_args.size()) + ".");
}

auto Parser::Args() const -> std::vector<std::string> { return m_args; }

auto Parser::MakeArgumentList() const -> std::string
{
    std::stringstream arg_list;

    if (not m_positions.empty())
    {
        arg_list << "\n\nPositions";
        for (const auto& position : m_positions)
            arg_list << position.Format();
    }

    arg_list << "\n\nOptions";
    for (const auto& option : m_options)
        arg_list << option->Format();
    arg_list << '\n';

    return arg_list.str();
}

auto Usage(const std::string& output) -> std::string { return output; }

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

auto Get(double& d) -> std::function<void(std::string)>
{
    return [&d](std::string value) { d = std::stod(value); };
}

} // namespace argon
