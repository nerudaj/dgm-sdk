#pragma once

#include <filesystem>

struct Settings
{
    bool skipMainMenu = false;
    std::filesystem::path resourcesDir = "../resources";
    float soundVolume = 50.f;
    float musicVolume = 50.f;
};
