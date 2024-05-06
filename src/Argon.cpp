module;

#include <argon/Export.hpp>

#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

export module argon;

export namespace argon {

/// \file

/// \brief Base type of all arguments
///
class ARGON_EXPORT Argument {
protected:
    static constexpr int m_format_width { 24 };

    std::string m_description;

public:
    Argument(std::string description)
        : m_description(std::move(description))
    {
    }
    virtual ~Argument() = default;
    Argument(const Argument&) = default;
    Argument(Argument&&) noexcept = default;
    Argument& operator=(const Argument&) = default;
    Argument& operator=(Argument&&) noexcept = default;

    [[nodiscard]] virtual auto format() const -> std::string = 0;
};

/// \brief Positional argument
///
class ARGON_EXPORT Position final : public Argument {
    std::string m_name;

public:
    Position(std::string name, const std::string& description);

    [[nodiscard]] auto format() const -> std::string override;
    [[nodiscard]] auto name() const -> std::string { return m_name; }
};

/// \brief Base type of all optional arguments
///
class ARGON_EXPORT Option : public Argument {
    std::set<std::string> m_flags;
    std::set<char> m_aliases;

protected:
    Option(const std::string& flags, const std::string& description);
    [[nodiscard]] auto flags() const -> std::vector<std::string>;

public:
    [[nodiscard]] auto format() const -> std::string override;
    virtual void find(std::vector<std::string_view>& args) const = 0;
};

/// \brief Optional argument with a simple binary state
///
class ARGON_EXPORT BasicOption final : public Option {
    std::function<void()> m_callback;

public:
    BasicOption(const std::string& flags, const std::string& description, std::function<void()> callback);
    void find(std::vector<std::string_view>& args) const override;
};

/// \brief Optional argument with an arbitrary value
///
class ARGON_EXPORT ValueOption final : public Option {
    std::function<void(std::string_view)> m_callback;

public:
    ValueOption(const std::string& flags,
                const std::string& description,
                std::function<void(std::string_view)> callback);
    [[nodiscard]] auto format() const -> std::string override;
    void find(std::vector<std::string_view>& args) const override;
};

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
    void add_option(const std::string& flags,
                    const std::string& description,
                    const Action& action,
                    const std::string& output);
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

// Implementation

Position::Position(std::string name, const std::string& description)
    : Argument(description)
    , m_name(std::move(name))
{
}

auto Position::format() const -> std::string
{
    std::stringstream out;
    out << std::setfill(' ');
    out << "\n  " << std::left << std::setw(m_format_width) << m_name << m_description;
    return out.str();
}

Option::Option(const std::string& flags, const std::string& description)
    : Argument(description)
{
    std::stringstream ss(flags);
    while (ss.good()) {
        std::string str;
        std::getline(ss, str, ',');
        if (str.size() == 1)
            m_aliases.emplace(str[0]);
        else
            m_flags.emplace(str);
    }
}

auto Option::flags() const -> std::vector<std::string>
{
    std::vector<std::string> flags;
    flags.reserve(m_aliases.size() + m_flags.size());
    for (const auto& alias : m_aliases)
        flags.emplace_back(std::string("-") + alias);
    for (const auto& flag : m_flags)
        flags.emplace_back("--" + flag);
    return flags;
}

auto Option::format() const -> std::string
{
    std::stringstream flags;
    std::string delim;
    for (const auto& flag : this->flags()) {
        flags << delim << flag;
        delim = ", ";
    }

    std::stringstream out;
    out << std::setfill(' ') << '\n';
    out << "  " << std::left << std::setw(m_format_width) << flags.str() << m_description;
    return out.str();
}

BasicOption::BasicOption(const std::string& flags, const std::string& description, std::function<void()> callback)
    : Option(flags, description)
    , m_callback(std::move(callback))
{
}

void BasicOption::find(std::vector<std::string_view>& args) const
{
    for (auto it = args.begin(); it < args.end(); ++it) {
        for (const auto& flag : flags()) {
            if (flag == *it) {
                args.erase(it);
                m_callback();
                return;
            }
        }
    }
}

ValueOption::ValueOption(const std::string& flags,
                         const std::string& description,
                         std::function<void(std::string_view)> callback)
    : Option(flags, description)
    , m_callback(std::move(callback))
{
}

auto ValueOption::format() const -> std::string
{
    std::stringstream flags;
    std::string delim;
    for (const auto& flag : this->flags()) {
        flags << delim << flag;
        delim = ", ";
    }
    flags << " <value>";

    std::stringstream out;
    out << std::setfill(' ') << '\n';
    out << "  " << std::left << std::setw(m_format_width) << flags.str() << m_description;
    return out.str();
}

void ValueOption::find(std::vector<std::string_view>& args) const
{
    for (auto it = args.begin(); it < args.end(); ++it) {
        for (const auto& flag : flags()) {
            if (flag == *it) {
                if (it + 1 == args.end())
                    throw std::runtime_error("Found option \"" + flag + "\" but no value was provided");
                m_callback(*(it + 1));
                args.erase(it, it + 2);
                return;
            }
        }
    }
}

Parser::Parser(const int argc, const char* const argv[])
    : m_program_name(std::string(argv[0]).substr(std::string(argv[0]).find_last_of('/') + 1))
    , m_args(argv + 1, argv + argc)
{
}

void Parser::add_option(const std::string& flags,
                        const std::string& description,
                        const Action& action,
                        const std::string& output)
{
    switch (action) {
    case USAGE:
        m_options.push_back(std::make_unique<BasicOption>(flags, description, [output, this]() {
            std::cerr << make_usage(output);
            std::exit(0);
        }));
        return;
    case PRINT:
        m_options.push_back(std::make_unique<BasicOption>(flags, description, [output]() {
            std::cerr << output << '\n';
            std::exit(0);
        }));
        return;
    }
}

void Parser::add_option(const std::string& flags, const std::string& description, bool& found)
{
    found = false;
    m_options.push_back(std::make_unique<BasicOption>(flags, description, [&found]() { found = true; }));
}

void Parser::add_position(const std::string& name, const std::string& description)
{
    m_positions.emplace_back(name, description);
}

auto Parser::get_position(const size_t index) const -> std::string_view { return args().at(index); }

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

auto Parser::args() const -> std::vector<std::string_view> { return m_args; }

auto Parser::make_usage(const std::string& help) const -> std::string
{
    std::stringstream usage;

    usage << "Usage\n  " << m_program_name;
    for (const auto& position : m_positions) {
        usage << " <" << position.name() << '>';
    }
    usage << " [options]";

    if (!help.empty())
        usage << "\n\n" << help.substr(help.find_first_not_of('\n'), help.size());

    if (!m_positions.empty()) {
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
