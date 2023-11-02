#pragma once

#include "core/Scene.hpp"
#include <DGM/DGM.hpp>

class [[nodiscard]] PhysicsEngine final
{
public:
    constexpr PhysicsEngine(Scene& scene) noexcept : scene(scene) {}

public:
    void update(const dgm::Time& time);

private:
    Scene& scene;
};
