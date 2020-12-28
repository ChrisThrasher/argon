#pragma once

#include <argon/Option.h>
#include <argon/Position.h>

#include <memory>

namespace argon
{

enum Action
{
    PRINT = 0,
    USAGE
};

class Parser
{
    auto MakeArgumentList() const -> std::string;

    const std::string m_program_name;

    std::vector<std::string> m_args{};
    std::vector<std::shared_ptr<argon::Option>> m_options{};
    std::vector<argon::Position> m_positions{};

public:
    Parser(const int, const char* const[]);
    void AddOption(const std::string&, const std::string&, const Action&, const std::string&);
    void AddOption(bool&, const std::string&, const std::string&);

    template <typename T>
    void AddOption(T&, const std::string&, const std::string&);

    void AddPosition(const std::string&, const std::string&);
    auto GetPosition(const size_t) -> std::string;
    void Parse();
    auto Args() const -> std::vector<std::string>;
};

Parser::Parser(const int argc, const char* const argv[])
    : m_program_name(std::string(argv[0]).substr(std::string(argv[0]).find_last_of('/') + 1))
    , m_args(std::vector<std::string>(argv + 1, argv + argc))
{
}

void Parser::AddOption(const std::string& flags,
                       const std::string& description,
                       const Action& action,
                       const std::string& output)
{
    switch (action)
    {
    case USAGE:
        m_options.push_back(std::make_shared<argon::BasicOption>(flags, description, [output, this]() {
            std::cerr << output << this->MakeArgumentList();
            std::exit(0);
        }));
        return;
    case PRINT:
        m_options.push_back(std::make_shared<argon::BasicOption>(flags, description, [output]() {
            std::cerr << output << '\n';
            std::exit(0);
        }));
        return;
    }
}

void Parser::AddOption(bool& found, const std::string& flags, const std::string& description)
{
    found = false;
    m_options.push_back(std::make_shared<argon::BasicOption>(flags, description, [&found]() { found = true; }));
}

template <typename T>
void Parser::AddOption(T& value, const std::string& flags, const std::string& description)
{
    m_options.push_back(std::make_shared<argon::ValueOption>(
        flags, description, [&value](const std::string& s) { std::istringstream(s) >> value; }));
}

void Parser::AddPosition(const std::string& name, const std::string& description)
{
    m_positions.push_back(argon::Position(name, description));
}

auto Parser::GetPosition(const size_t index) -> std::string { return Args().at(index); }

void Parser::Parse()
{
    for (const auto& option : m_options)
        option->Find(m_args);

    if (m_positions.size() > m_args.size())
    {
        std::stringstream what;
        what << "Expected " << m_positions.size() << " positional arguments. Received " << m_args.size();
        what << MakeArgumentList();
        throw std::runtime_error(what.str());
    }
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

} // namespace argon
