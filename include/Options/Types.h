#pragma once

#include <functional>
#include <string>
#include <vector>

namespace opts
{

class ExitOption
{
    const std::vector<std::string> flags;
    const std::string description;
    const std::function<std::string()> output;

public:
    ExitOption(const std::vector<std::string>& a_flags,
               const std::string& a_description,
               const std::function<std::string()>& a_output)
        : flags([a_flags]() {
            std::vector<std::string> tmp;
            for (const auto& flag : a_flags)
            {
                if (flag.size() == 1)
                    tmp.push_back('-' + flag);
                else
                    tmp.push_back("--" + flag);
            }
            return tmp;
        }())
        , description(a_description)
        , output(a_output)
    {
    }

    auto Flags() const -> std::vector<std::string> { return flags; }
    auto Description() const -> std::string { return description; }
    auto Output() const -> std::string { return output(); }
};

} // namespace opts
