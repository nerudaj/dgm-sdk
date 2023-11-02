#pragma once

import Memory;

#include <core/Scene.hpp>
#include <events/EventQueue.hpp>
#include <events/GameRuleEvents.hpp>
#include <DGM/DGM.hpp>

class [[nodiscard]] GameRulesEngine final
{
public:
    GameRulesEngine(Scene& scene, mem::Rc<EventQueue> eventQueue) noexcept : scene(scene), eventQueue(eventQueue) {}

public: // Must visit on all related events
    void operator()(const DummyGameEvent&) {}

public:
    void update(const dgm::Time& time);

private:
    Scene& scene;
	mem::Rc<EventQueue> eventQueue;
};
