
#pragma once

#include <string>


class Settings
{
public:
    std::string Password;
    bool ShowProgress{ false };
    std::string Username;
    bool UseAuthentication{ false };
    bool VerboseOutput{ false };
};
