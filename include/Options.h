#pragma once

#include <string>

class Options
{
    bool m_help_provided{false};
    bool m_version_provided{false};

    std::string m_help_text{};
    std::string m_version_text{};

public:
    void Parse(const int, const char* const[]) const;
    void RegisterHelp(const std::string&);
    void RegisterVersion(const std::string&);  
};

void Options::Parse(const int argc, const char* const argv[]) const
{
    (void)argc;
    (void)argv;
}

void Options::RegisterHelp(const std::string& help_text)
{
    m_help_provided = true;
    m_help_text = help_text;
}

void Options::RegisterVersion(const std::string& version_text)
{
    m_version_provided = true;
    m_version_text = version_text;
}