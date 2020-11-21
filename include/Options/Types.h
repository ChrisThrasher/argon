#pragma once

#include <functional>
#include <string>
#include <vector>

namespace opts
{

class ExitOption
{
    const std::vector<std::string> m_flags;
    const std::string m_description;
    const std::function<std::string()> m_output;

public:
    ExitOption(const std::vector<std::string>& flags,
               const std::string& description,
               const std::function<std::string()>& output)
        : m_flags([flags]() {
            std::vector<std::string> tmp;
            for (const auto& flag : flags)
            {
                if (flag.size() == 1)
                    tmp.push_back('-' + flag);
                else
                    tmp.push_back("--" + flag);
            }
            return tmp;
        }())
        , m_description(description)
        , m_output(output)
    {
    }

    auto Flags() const -> std::vector<std::string> { return m_flags; }
    auto Description() const -> std::string { return m_description; }
    auto Output() const -> std::string { return m_output(); }
};

} // namespace opts
