#include <argon/Position.hpp>

#include <iomanip>
#include <sstream>

namespace argon {

Position::Position(const std::string& name, const std::string& description)
    : Argument(description)
    , m_name(name)
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