#pragma once

#include <string>

namespace argon {

class Argument {
protected:
    const int m_format_width { 24 };

public:
    virtual auto format() const -> std::string = 0;
};

}
