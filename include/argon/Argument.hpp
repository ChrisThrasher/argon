#pragma once

#include <argon/Export.hpp>

#include <string>

namespace argon {

/// \file

/// \brief Base type of all arguments
///
class ARGON_EXPORT Argument {
protected:
    static inline constexpr int m_format_width { 24 };

    std::string m_description;

public:
    Argument(std::string description);
    virtual ~Argument() = default;
    [[nodiscard]] virtual auto format() const -> std::string = 0;
};

}
