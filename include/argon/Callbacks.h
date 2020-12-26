#pragma once

#include <functional>
#include <iostream>
#include <string>

namespace argon
{

auto Usage(const std::string& output) -> std::string { return output; }

auto Print(const std::string& output) -> std::function<void()>
{
    return [output]() {
        std::cerr << output << std::endl;
        std::exit(0);
    };
}

} // namespace argon
