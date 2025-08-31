#pragma once

#include <argon/Option.hpp>
#include <argon/Position.hpp>

#include <cstdint>
#include <memory>
#include <sstream>
#include <string_view>

namespace argon {

/// \file

/// \brief Special tags for options
///
enum Action : std::uint8_t {
    PRINT, ///< Print message to console then exit
    USAGE ///< Print usage text
};

/// \brief Argument parser
///
class ARGON_EXPORT Parser {
    [[nodiscard]] auto make_usage(const std::string& help) const -> std::string;

    std::string m_program_name;

    std::vector<std::string_view> m_args;
    std::vector<std::shared_ptr<Option>> m_options;
    std::vector<Position> m_positions;

public:
    Parser(int argc, const char* const argv[]);
    void add_option(const std::string& flags, const std::string& description, Action action, const std::string& output);
    void add_option(const std::string& flags, const std::string& description, bool& found);

    template <typename T>
    void add_option(const std::string& flags, const std::string& description, T& value);

    void add_position(const std::string& name, const std::string& description);
    void parse();

    [[nodiscard]] auto get_position(size_t index) const -> std::string_view;
    [[nodiscard]] auto args() const -> std::vector<std::string_view>;
};

template <typename T>
void Parser::add_option(const std::string& flags, const std::string& description, T& value)
{
    m_options.push_back(std::make_unique<ValueOption>(
        flags, description, [&value](std::string_view s) { std::istringstream(std::string(s)) >> value; }));
}

}
