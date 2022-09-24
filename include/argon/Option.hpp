#pragma once

#include <argon/Argument.hpp>

#include <functional>
#include <set>
#include <vector>

namespace argon {

class ARGON_EXPORT Option : public Argument {
    std::set<std::string> m_flags;
    std::set<char> m_aliases;

protected:
    Option(const std::string& flags, const std::string& description);
    [[nodiscard]] auto flags() const -> std::vector<std::string>;

public:
    [[nodiscard]] auto format() const -> std::string override;
    virtual void find(std::vector<std::string>& args) const = 0;
};

class ARGON_EXPORT BasicOption final : public Option {
    std::function<void()> m_callback;

public:
    BasicOption(const std::string& flags, const std::string& description, std::function<void()> callback);
    void find(std::vector<std::string>& args) const override;
};

class ARGON_EXPORT ValueOption final : public Option {
    std::function<void(std::string)> m_callback;

public:
    ValueOption(const std::string& flags, const std::string& description, std::function<void(std::string)> callback);
    [[nodiscard]] auto format() const -> std::string override;
    void find(std::vector<std::string>& args) const override;
};

}
