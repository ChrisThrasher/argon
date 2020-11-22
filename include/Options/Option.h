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
protected:
    auto Flags() const -> std::vector<std::string>
    {
        std::vector<std::string> flags;
        for (const auto& alias : m_aliases)
            flags.push_back(std::string("-") + alias);
        for (const auto& flag : m_flags)
            flags.push_back("--" + flag);
        return flags;
    }

    std::set<std::string> m_flags;
    std::set<char> m_aliases;
    const std::string m_description;

    Option(const std::string& flags, const std::string& description)
        : m_description(description)
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

public:
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

    virtual void Find(const std::vector<std::string>& args) const = 0;
};

class ExitOption final : public Option
{
    const std::function<std::string()> m_output;

public:
    ExitOption(const std::string& flags, const std::string& description, const std::string& output)
        : Option(flags, description)
        , m_output([output]() { return output; })
    {
    }

    ExitOption(const std::string& flags, const std::string& description, const std::function<std::string()>& output)
        : Option(flags, description)
        , m_output(output)
    {
    }

    virtual void Find(const std::vector<std::string>& args) const
    {
        for (const auto& flag : Flags())
        {
            if (args[0] == flag)
            {
                std::cout << m_output() << '\n';
                std::exit(0);
            }
        }
    }
};

class BoolOption final : public Option
{
    bool& m_value;

public:
    BoolOption(const std::string& flag, const std::string& description, bool& value)
        : Option(flag, description)
        , m_value(value)
    {
    }

    virtual void Find(const std::vector<std::string>& args) const
    {
        for (const auto& flag : Flags())
        {
            for (const auto& arg : args)
            {
                if (flag == arg)
                {
                    m_value = true;
                    return;
                }
            }
        }
    }
};

} // namespace opts
