#pragma once

#include <functional>
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
    ExitOption(const std::string flag,
               const char alias,
               const std::string& description,
               const std::function<std::string()>& output)
        : m_flag(flag)
        , m_alias(alias)
        , m_description(description)
        , m_output(output)
    {
    }

    auto Flags() const -> std::vector<std::string> { return {std::string("-") + m_alias, "--" + m_flag}; }
    auto Description() const -> std::string { return m_description; }
    auto Output() const -> std::string { return m_output(); }
};

} // namespace opts
