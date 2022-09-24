#include <argon/Position.hpp>

#include <iomanip>
#include <sstream>
#include <utility>

namespace argon {

Position::Position(std::string name, const std::string& description)
    : Argument(description)
    , m_name(std::move(name))
{
}

auto Position::format() const -> std::string
{
    std::stringstream out;
    out << std::setfill(' ');
    out << "\n  " << std::left << std::setw(m_format_width) << m_name << m_description;
    return out.str();
}

}
