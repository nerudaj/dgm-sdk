#pragma once

#include <filesystem>

/// <summary>
/// Command-line settings
/// </summary>
struct CmdSettings
{
    bool skipMainMenu = false;
    std::filesystem::path resourcesDir = "../resources";
};