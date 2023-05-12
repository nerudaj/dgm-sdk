#pragma once

#include "AudioEvents.hpp"
#include <DGM/DGM.hpp>

class AudioEngine final
{
public: // Must visit on all related events
    void operator()(const AudioEvent& e) {}

public:
    void update(const dgm::Time& time);
};
