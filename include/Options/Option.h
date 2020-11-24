#pragma once

#include <functional>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace opts
{

class Option
{
    std::set<std::string> m_flags;
    std::set<char> m_aliases;
    const std::string m_description;
    const std::function<void()> m_callback;

    auto Flags() const -> std::vector<std::string>
    {
        std::vector<std::string> flags;
        for (const auto& alias : m_aliases)
            flags.push_back(std::string("-") + alias);
        for (const auto& flag : m_flags)
            flags.push_back("--" + flag);
        return flags;
    }

public:
    Option(const std::string& flags, const std::string& description, const std::function<void()>& callback)
        : m_description(description)
        , m_callback(callback)
    {
        std::stringstream ss(flags);
        while (ss.good())
        {
            std::string str;
            std::getline(ss, str, ',');
            if (str.size() == 1)
                m_aliases.emplace(str[0]);
            else
                m_flags.emplace(str);
        }
    }

    auto Format() const -> std::string
    {
        std::string flags;
        std::string delim = "";
        for (const auto& flag : Flags())
        {
            flags += delim + flag;
            delim = ", ";
        }

        std::stringstream out;
        out << std::setfill(' ');
        out << "\n  " << std::left << std::setw(16) << flags << m_description;
        return out.str();
    }

    void Find(const std::vector<std::string>& args) const
    {
        for (const auto& flag : Flags())
            for (const auto& arg : args)
                if (flag == arg)
                    return m_callback();
    }
};

} // namespace opts
