#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG
    // release build
    return "assets/";
#else
    // Debug mode
    return "/Users/joel/Documents/dev/LightYears/LightYearsGame/assets/";
#endif
}
