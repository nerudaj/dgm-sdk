#pragma once

import Memory;

#include "audio/AudioPlayer.hpp"
#include <DGM/DGM.hpp>

class [[nodiscard]] AudioEngine final
{
public:
    AudioEngine(
        mem::Rc<const dgm::ResourceManager> resmgr,
        mem::Rc<AudioPlayer> audioPlayer) noexcept
        : resmgr(resmgr), audioPlayer(audioPlayer)
    {
    }

public:
    void update(const dgm::Time& time);

private:
    mem::Rc<const dgm::ResourceManager> resmgr;
    mem::Rc<AudioPlayer> audioPlayer;
};
