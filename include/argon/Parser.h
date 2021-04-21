#pragma once

#include <argon/Option.h>
#include <argon/Position.h>

#include <memory>
#include <sstream>

namespace argon {

enum Action { PRINT = 0, USAGE };

class Parser {
    auto make_usage(const std::string&) const -> std::string;

    const std::string m_program_name;

    std::vector<std::string> m_args {};
    std::vector<std::shared_ptr<argon::Option>> m_options {};
    std::vector<argon::Position> m_positions {};

public:
    Parser(const int, const char* const[]);
    void add_option(const std::string&, const std::string&, const Action&, const std::string&);
    void add_option(bool&, const std::string&, const std::string&);

    template <typename T>
    void add_option(T&, const std::string&, const std::string&);

    void add_position(const std::string&, const std::string&);
    auto get_position(const size_t) -> std::string;
    void parse();
    auto args() const -> std::vector<std::string>;
};

template <typename T>
void Parser::add_option(T& value, const std::string& flags, const std::string& description)
{
    m_options.push_back(std::make_shared<argon::ValueOption>(
        flags, description, [&value](const std::string& s) { std::istringstream(s) >> value; }));
}

}
