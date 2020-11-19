#pragma once

#include <Options/Types.h>

#include <iomanip>
#include <sstream>

auto FormatFlags(const std::vector<std::string>& flags) -> std::string
{
    std::stringstream out;
    for (size_t i = 0; i + 1 < flags.size(); ++i)
        out << flags[i] << ", ";
    out << flags.back();
    return out.str();
}

auto FormatOption(const TerminalOption& option) -> std::string
{
    std::stringstream out;
    out << std::setfill(' ');
    if (not option.flags.empty())
    {
        out << "\n  " << std::left << std::setw(16) << FormatFlags(option.flags) << option.description;
    }
    return out.str();
}