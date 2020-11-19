#pragma once

#include <string>
#include <vector>

struct ExitOption
{
    std::vector<std::string> flags;
    std::string description;
    std::string output;
};