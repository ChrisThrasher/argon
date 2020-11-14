#pragma once

#include <iostream>
#include <string>
#include <vector>

using ExitItem = std::pair<std::vector<std::string>, std::string>;

class Options
{
    const std::vector<std::string> args{};

public:
    Options(const int, const char* const[]);
    void RegisterExitItem(const ExitItem&);
};

Options::Options(const int argc, const char* const argv[])
    : args(std::vector<std::string>(argv + 1, argv + argc))
{
}

void Options::RegisterExitItem(const ExitItem& exit_item)
{
    for (const auto& arg : args)
        for (const auto& flag : exit_item.first)
            if (arg == flag)
                std::cout << exit_item.second << '\n';
}
