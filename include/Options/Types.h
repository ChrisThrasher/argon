#pragma once

#include <functional>
#include <string>
#include <vector>

namespace opts
{

struct ExitOption
{
    std::vector<std::string> flags;
    const std::string description;
    const std::function<std::string()> output;

    ExitOption(const std::vector<std::string>& a_flags,
               const std::string& a_description,
               const std::function<std::string()>& a_output)
        : description(a_description)
        , output(a_output)
    {
        for (const auto& flag : a_flags)
        {
            if (flag.size() == 1)
                flags.push_back('-' + flag);
            else
                flags.push_back("--" + flag);
        }
    }
};

} // namespace opts
