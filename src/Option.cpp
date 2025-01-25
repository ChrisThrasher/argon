#include <argon/Option.hpp>

#include <iomanip>
#include <sstream>
#include <utility>

namespace argon {

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

}
