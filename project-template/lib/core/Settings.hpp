#pragma once

#include <Config.hpp>

struct Settings
{
	float soundVolume = 50.f;
	float musicVolume = 50.f;

	std::string resourcesDir = "../resources";
	bool skipMainMenu = false;
};
