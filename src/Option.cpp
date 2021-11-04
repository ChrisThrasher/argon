#include <argon/Option.h>

#include <iomanip>
#include <iostream>
#include <sstream>

namespace argon {

Option::Option(const std::string& flags, const std::string& description, const std::string& name)
    : Argument(name, description)
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
    for (const auto& alias : m_aliases)
        flags.push_back(std::string("-") + alias);
    for (const auto& flag : m_flags)
        flags.push_back("--" + flag);
    return flags;
}

auto Option::format() const -> std::string
{
    std::stringstream flags;
    std::string delim = "";
    for (const auto& flag : this->flags()) {
        flags << delim << flag;
        delim = ", ";
    }
    flags << ' ' << m_name;

    std::stringstream out;
    out << std::setfill(' ');
    out << "\n  " << std::left << std::setw(m_format_width) << flags.str() << m_description;
    return out.str();
}

BasicOption::BasicOption(const std::string& flags,
                         const std::string& description,
                         const std::function<void()>& callback)
    : Option(flags, description)
    , m_callback(callback)
{
}

void BasicOption::find(std::vector<std::string>& args) const
{
    for (auto it = args.begin(); it < args.end(); ++it) {
        for (const auto& flag : flags()) {
            if (flag == *it) {
                args.erase(it);
                return m_callback();
            }
        }
    }
}

ValueOption::ValueOption(const std::string& flags,
                         const std::string& description,
                         const std::function<void(std::string)>& callback)
    : Option(flags, description, "<value> ")
    , m_callback(callback)
{
}

void ValueOption::find(std::vector<std::string>& args) const
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
