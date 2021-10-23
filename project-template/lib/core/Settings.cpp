#include "Settings.hpp"

void Settings::loadFrom(const cfg::Ini& ini) {
	if (ini.hasSection("Audio") && ini["Audio"].hasKey("soundVolume"))
		soundVolume = ini["Audio"].at("soundVolume").asFloat();
	if (ini.hasSection("Audio") && ini["Audio"].hasKey("musicVolume"))
		musicVolume = ini["Audio"].at("musicVolume").asFloat();
}

void Settings::saveTo(cfg::Ini& ini) {
	ini["Audio"]["soundVolume"] = soundVolume;
	ini["Audio"]["musicVolume"] = musicVolume;
}
