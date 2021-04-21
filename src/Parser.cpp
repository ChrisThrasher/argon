#include <argon/Parser.h>

#include <iostream>

namespace argon {

Parser::Parser(const int argc, const char* const argv[])
    : m_program_name(std::string(argv[0]).substr(std::string(argv[0]).find_last_of('/') + 1))
    , m_args(std::vector<std::string>(argv + 1, argv + argc))
{
}

void Parser::add_option(const std::string& flags,
                        const std::string& description,
                        const Action& action,
                        const std::string& output)
{
    switch (action) {
    case USAGE:
        m_options.push_back(std::make_shared<argon::BasicOption>(flags, description, [output, this]() {
            std::cerr << make_usage(output);
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

void Parser::add_option(bool& found, const std::string& flags, const std::string& description)
{
    found = false;
    m_options.push_back(std::make_shared<argon::BasicOption>(flags, description, [&found]() { found = true; }));
}

void Parser::add_position(const std::string& name, const std::string& description)
{
    m_positions.push_back(argon::Position(name, description));
}

auto Parser::get_position(const size_t index) -> std::string { return args().at(index); }

void Parser::parse()
{
    for (const auto& option : m_options)
        option->find(m_args);

    if (m_positions.size() > m_args.size()) {
        std::stringstream what;
        what << "Expected " << m_positions.size() << " positional arguments. Received " << m_args.size();
        what << "\n\n" << make_usage("");
        throw std::runtime_error(what.str());
    }
}

auto Parser::args() const -> std::vector<std::string> { return m_args; }

auto Parser::make_usage(const std::string& help) const -> std::string
{
    std::stringstream usage;

    usage << "Usage\n  " << m_program_name;
    for (const auto& position : m_positions) {
        usage << " <" << position.name() << '>';
    }
    usage << " [options]";

    if (not help.empty())
        usage << "\n\n" << help.substr(help.find_first_not_of('\n'), help.size());

    if (not m_positions.empty()) {
        usage << "\n\nPositions";
        for (const auto& position : m_positions)
            usage << position.format();
    }

    usage << "\n\nOptions";
    for (const auto& option : m_options)
        usage << option->format();
    usage << '\n';

    return usage.str();
}

}