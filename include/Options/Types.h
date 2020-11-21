#pragma once

#include <functional>
#include <string>
#include <vector>

namespace opts
{

struct ExitOption
{
    const std::vector<std::string> flags;
    const std::string description;
    const std::function<std::string()> output;
};

} // namespace opts
