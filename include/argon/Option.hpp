#pragma once

#include <argon/Argument.hpp>

#include <functional>
#include <set>
#include <string_view>
#include <vector>

namespace argon {

/// \file

/// \brief Base type of all optional arguments
///
class ARGON_EXPORT Option : public Argument {
    std::set<std::string> m_flags;
    std::set<char> m_aliases;

protected:
    Option(const std::string& flags, const std::string& description);
    [[nodiscard]] auto flags() const -> std::vector<std::string>;

public:
    [[nodiscard]] auto format() const -> std::string override;
    virtual void find(std::vector<std::string_view>& args) const = 0;
};

/// \brief Optional argument with a simple binary state
///
class ARGON_EXPORT BasicOption final : public Option {
    std::function<void()> m_callback;

public:
    BasicOption(const std::string& flags, const std::string& description, std::function<void()> callback);
    void find(std::vector<std::string_view>& args) const override;
};

/// \brief Optional argument with an arbitrary value
///
class ARGON_EXPORT ValueOption final : public Option {
    std::function<void(std::string_view)> m_callback;

public:
    ValueOption(const std::string& flags,
                const std::string& description,
                std::function<void(std::string_view)> callback);
    [[nodiscard]] auto format() const -> std::string override;
    void find(std::vector<std::string_view>& args) const override;
};

}
