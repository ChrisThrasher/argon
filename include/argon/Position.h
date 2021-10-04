#pragma once

#include <argon/Argument.h>

namespace argon {

class Position final : public Argument {
public:
    Position(const std::string& name, const std::string& description);

    auto format() const -> std::string override;
    auto name() const -> std::string { return m_name; }
};

}
