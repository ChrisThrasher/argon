#include <argon/Argument.hpp>
#include <format>
#include <utility>

namespace argon {

Argument::Argument(std::string description)
    : m_description(std::move(description))
{
}

[[nodiscard]] auto Argument::format(const std::string_view string) const -> std::string
{
    return std::format("\n  {:<24}{}", string, m_description);
}
}
