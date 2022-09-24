#pragma once

#include <argon/Argument.hpp>

namespace argon {

class ARGON_EXPORT Position final : public Argument {
    std::string m_name;

public:
    Position(std::string name, const std::string& description);

    [[nodiscard]] auto format() const -> std::string override;
    [[nodiscard]] auto name() const -> std::string { return m_name; }
};

}
