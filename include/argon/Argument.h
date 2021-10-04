#pragma once

#include <string>

namespace argon {

class Argument {
protected:
    static constexpr int m_format_width { 24 };

public:
    virtual auto format() const -> std::string = 0;
};

}
