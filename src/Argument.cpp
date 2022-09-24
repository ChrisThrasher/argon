#include <argon/Argument.hpp>
#include <utility>

namespace argon {

Argument::Argument(std::string description)
    : m_description(std::move(description))
{
}
}
