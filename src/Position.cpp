#include <argon/Position.hpp>

#include <utility>

namespace argon {

Position::Position(std::string name, const std::string& description)
    : Argument(description)
    , m_name(std::move(name))
{
}

auto Position::format() const -> std::string { return Argument::format(m_name); }

}
