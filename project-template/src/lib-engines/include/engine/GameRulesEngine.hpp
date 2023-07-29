#pragma once

#include "GameRuleEvents.hpp"
#include "Scene.hpp"
#include <DGM/DGM.hpp>

class GameRulesEngine final
{
public:
    [[nodiscard]] GameRulesEngine(Scene& scene) noexcept : scene(scene) {}

public: // Must visit on all related events
    void operator()(const DummyGameEvent&) {}

public:
    void update(const dgm::Time& time);

private:
    Scene& scene;
};
