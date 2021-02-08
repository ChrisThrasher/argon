#pragma once

#include <argon/Argument.h>

namespace argon {

class Position final : public Argument {
    std::string m_name;
    std::string m_description;

public:
    Position(const std::string&, const std::string&);

    virtual auto Format() const -> std::string;
    auto Name() const -> std::string { return m_name; }
};

} // namespace argon
