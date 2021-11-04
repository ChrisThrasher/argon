#pragma once

#include <argon/argument.h>

namespace argon {

class Position final : public Argument {
    std::string m_name;

public:
    Position(const std::string& name, const std::string& description);

    auto format() const -> std::string override;
    auto name() const -> std::string { return m_name; }
};

}
