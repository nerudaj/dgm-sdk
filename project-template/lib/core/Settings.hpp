#pragma once

#include <Config.hpp>

struct Settings {
	float soundVolume = 50.f;
	float musicVolume = 50.f;

	void loadFrom(const cfg::Ini& ini);
	void saveTo(cfg::Ini& ini);
};

/// This value is populated by cmake variable from settings.cmake
const std::string GAME_TITLE = "Example";
