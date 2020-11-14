#pragma once

#include <iostream>
#include <string>
#include <vector>

using ExitItem = std::pair<std::vector<std::string>, std::string>;

class Options
{
    std::vector<ExitItem> m_exit_items{};

public:
    void Parse(const int, const char* const[]) const;
    void RegisterExitItem(const ExitItem&);
};

void Options::Parse(const int argc, const char* const argv[]) const
{
    for (int i = 1; i < argc; ++i)
        for (const auto& exit_item : m_exit_items)
            for (const auto& flag : exit_item.first)
                if (argv[i] == flag)
                    std::cout << exit_item.second << '\n';
}

void Options::RegisterExitItem(const ExitItem& exit_item)
{
    m_exit_items.push_back(exit_item);
}
