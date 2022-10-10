#pragma once

#include <argon/Option.hpp>
#include <argon/Position.hpp>

#include <memory>
#include <sstream>

namespace argon {

enum Action { PRINT, USAGE };

class ARGON_EXPORT Parser {
    [[nodiscard]] auto make_usage(const std::string& help) const -> std::string;

    std::string m_program_name;

    std::vector<std::string> m_args;
    std::vector<std::shared_ptr<Option>> m_options;
    std::vector<Position> m_positions;

public:
    Parser(int argc, const char* const argv[]);
    void add_option(const std::string& flags,
                    const std::string& description,
                    const Action& action,
                    const std::string& output);
    void add_option(bool& found, const std::string& flags, const std::string& description);

    template <typename T>
    void add_option(T& value, const std::string& flags, const std::string& description);

    void add_position(const std::string& name, const std::string& description);
    void parse();

    [[nodiscard]] auto get_position(size_t index) const -> std::string;
    [[nodiscard]] auto args() const -> std::vector<std::string>;
};

template <typename T>
void Parser::add_option(T& value, const std::string& flags, const std::string& description)
{
    m_options.emplace_back(std::make_unique<ValueOption>(
        flags, description, [&value](const std::string& s) { std::istringstream(s) >> value; }));
}

}
