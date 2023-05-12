#pragma once

#include "AudioEvents.hpp"
#include "audio/AudioPlayer.hpp"
#include <DGM/DGM.hpp>

class AudioEngine final
{
public:
    [[nodiscard]] AudioEngine(
        const dgm::ResourceManager& resmgr, AudioPlayer& audioPlayer) noexcept
        : resmgr(resmgr), audioPlayer(audioPlayer)
    {
    }

public: // Must visit on all related events
    void operator()(const DummyAudioEvent& e) {}

public:
    void update(const dgm::Time& time);

private:
    const dgm::ResourceManager& resmgr;
    AudioPlayer& audioPlayer;
};
