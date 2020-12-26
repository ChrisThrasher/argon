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

auto Find(bool& exists) -> std::function<void()>
{
    exists = false;
    return [&exists]() { exists = true; };
}

auto Get(std::string& str) -> std::function<void(std::string)>
{
    return [&str](std::string value) { str = value; };
}

auto Get(int& i) -> std::function<void(std::string)>
{
    return [&i](std::string value) { i = std::stoi(value); };
}

auto Get(double& d) -> std::function<void(std::string)>
{
    return [&d](std::string value) { d = std::stod(value); };
}

} // namespace argon
