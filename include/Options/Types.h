#pragma once

#include <functional>
#include <string>
#include <vector>

namespace opts
{

struct ExitOption
{
    std::vector<std::string> flags;
    std::string description;
    std::function<std::string()> output;
};

} // namespace opts
