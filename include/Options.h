#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>

class Options
{
    const std::vector<std::string> args{};

public:
    Options(const int, const char* const[]);
    void ExitItem(const std::vector<std::string>&, const std::string&) const;
    std::optional<int> Int(const std::vector<std::string>&) const;
};

Options::Options(const int argc, const char* const argv[])
    : args(std::vector<std::string>(argv + 1, argv + argc))
{
}

void Options::ExitItem(const std::vector<std::string>& flags, const std::string& text) const
{
    for (const auto& arg : args)
        for (const auto& flag : flags)
            if (arg == flag)
                std::cout << text << '\n';
}

std::optional<int> Options::Int(const std::vector<std::string>& flags) const
{
    for (size_t i = 0; i < args.size(); ++i)
        for (const auto& flag : flags)
            if (args[i] == flag)
                return std::stoi(args.at(i + 1));
    return std::nullopt;
}