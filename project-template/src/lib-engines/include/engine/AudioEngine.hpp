#pragma once

#include "AudioEvents.hpp"
#include "audio/AudioPlayer.hpp"
#include <DGM/DGM.hpp>

import Memory;

class AudioEngine final
{
public:
    [[nodiscard]] AudioEngine(
        mem::Rc<const dgm::ResourceManager> resmgr,
        mem::Rc<AudioPlayer> audioPlayer) noexcept
        : resmgr(resmgr), audioPlayer(audioPlayer)
    {
    }

public: // Must visit on all related events
    void operator()(const DummyAudioEvent& e) {}

public:
    void update(const dgm::Time& time);

private:
    mem::Rc<const dgm::ResourceManager> resmgr;
    mem::Rc<AudioPlayer> audioPlayer;
};
