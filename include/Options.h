#pragma once

#include <iostream>
#include <string>
#include <vector>

class Options
{
    const std::vector<std::string> args{};

public:
    Options(const int, const char* const[]);
    void RegisterExitItem(const std::vector<std::string>&, const std::string&) const;
};

Options::Options(const int argc, const char* const argv[])
    : args(std::vector<std::string>(argv + 1, argv + argc))
{
}

void Options::RegisterExitItem(const std::vector<std::string>& flags, const std::string& text) const
{
    for (const auto& arg : args)
        for (const auto& flag : flags)
            if (arg == flag)
                std::cout << text << '\n';
}
