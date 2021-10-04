#pragma once

#include <string>

namespace argon {

class Argument {
protected:
    static constexpr int m_format_width { 24 };

    std::string m_name;
    std::string m_description;

public:
    Argument(const std::string& name, const std::string& description);
    virtual auto format() const -> std::string = 0;
};

}
