#pragma once

#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace opts
{

class ExitOption
{
    const std::string m_flag;
    const char m_alias;
    const std::string m_description;
    const std::function<std::string()> m_output;

public:
    ExitOption(const std::string& flag,
               const char alias,
               const std::string& description,
               const std::function<std::string()>& output)
        : m_flag(flag)
        , m_alias(alias)
        , m_description(description)
        , m_output(output)
    {
    }

    void Find(const std::vector<std::string>& args) const
    {
        if (args.size() == 1)
            return;

        for (const auto& flag : Flags())
        {
            if (args[1] == flag)
            {
                std::cout << m_output() << '\n';
                std::exit(0);
            }
        }
    }

    auto Format() const -> std::string
    {
        const auto flags = std::string("-") + m_alias + ", --" + m_flag;

        std::stringstream out;
        out << std::setfill(' ');
        out << "\n  " << std::left << std::setw(16) << flags << m_description;
        return out.str();
    }

    auto Flags() const -> std::vector<std::string> { return {std::string("-") + m_alias, "--" + m_flag}; }
};

} // namespace opts
