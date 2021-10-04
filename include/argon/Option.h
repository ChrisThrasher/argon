#pragma once

#include <argon/Argument.h>

#include <functional>
#include <set>
#include <vector>

namespace argon {

class Option : public Argument {
    std::set<std::string> m_flags;
    std::set<char> m_aliases;

protected:
    Option(const std::string& flags, const std::string& description, const std::string& name = "");
    auto flags() const -> std::vector<std::string>;

public:
    auto format() const -> std::string override;
    virtual void find(std::vector<std::string>& args) const = 0;
};

class BasicOption final : public Option {
    const std::function<void()> m_callback;

public:
    BasicOption(const std::string& flags, const std::string& description, const std::function<void()>& callback);
    void find(std::vector<std::string>& args) const override;
};

class ValueOption final : public Option {
    const std::function<void(std::string)> m_callback;

public:
    ValueOption(const std::string& flags,
                const std::string& description,
                const std::function<void(std::string)>& callback);
    void find(std::vector<std::string>& args) const override;
};

}
