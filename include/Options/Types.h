#pragma once

#include <string>
#include <vector>

struct TerminalOption
{
    std::vector<std::string> flags;
    std::string description;
    std::string output;
};