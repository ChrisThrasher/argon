#include <argon/Argument.h>

namespace argon {
constexpr int Argument::m_format_width;

Argument::Argument(const std::string& description)
    : m_description(description)
{
}
}
