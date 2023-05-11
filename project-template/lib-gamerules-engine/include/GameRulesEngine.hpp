#pragma once

#include "GameRuleEvents.hpp"
#include <DGM/DGM.hpp>

class GameRulesEngine final
{
public: // Must visit on all related events
    void operator()(const DummyGameEvent& e) {}

public:
    void update(const dgm::Time& time);
};
