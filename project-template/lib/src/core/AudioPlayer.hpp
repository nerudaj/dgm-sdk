#pragma once

#include <vector>
#include <DGM/DGM.hpp>

constexpr unsigned CHANNEL_COUNT = 8;

class AudioPlayer {
private:
    std::vector<sf::Sound> channels;
    const dgm::ResourceManager &resmgr;

    [[nodiscard]] bool isChannelActive(const unsigned channel) const {
        return channels[channel].getStatus() == sf::Sound::Status::Playing;
    }

public:
    void playSoundOnChannel(const std::string &soundName, const unsigned channel, const bool force = false);

    void stopChannel(const unsigned channel);

    void setSoundVolume(const float volume);

    AudioPlayer(const unsigned channelCount, const dgm::ResourceManager &resmgr) : channels(channelCount), resmgr(resmgr) {}
	~AudioPlayer();
};
