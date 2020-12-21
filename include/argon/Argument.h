#pragma once

#include <string>

namespace argon
{

class Argument
{
protected:
    const int m_format_width{16};

public:
    virtual auto Format() const -> std::string = 0;
};

} // namespace argon