#pragma once

#include "PhysicsEvents.hpp"
#include <DGM/DGM.hpp>

class PhysicsEngine final
{
public: // Must visit on all related events
    void operator()(const DummyPhysicsEvent& e) {}

public:
    void update(const dgm::Time& time);
};
