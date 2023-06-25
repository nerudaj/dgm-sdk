#pragma once

#include "Settings.hpp"
#include "app/GuiWrapper.hpp"
#include "audio/AudioPlayer.hpp"
#include "engine/AudioEngine.hpp"
#include "engine/GameRulesEngine.hpp"
#include "engine/PhysicsEngine.hpp"
#include "engine/RenderingEngine.hpp"
#include <DGM/dgm.hpp>

import Memory;

class AppStateIngame final : public dgm::AppState
{
public:
    [[nodiscard]] AppStateIngame(
        dgm::App& app,
        mem::Rc<const dgm::ResourceManager> resmgr,
        mem::Rc<GuiWrapper> gui,
        mem::Rc<Settings> settings,
        mem::Rc<AudioPlayer> audioPlayer);

public:
    virtual void input() override;
    virtual void update() override;
    virtual void draw() override;

    virtual [[nodiscard]] bool isTransparent() const noexcept override
    {
        return false;
    }

    virtual void restoreFocus() override {}

protected:
    [[nodiscard]] static Scene constructScene(
        const dgm::ResourceManager& resmgr, const sf::Vector2f& baseResolution);

protected:
    mem::Rc<const dgm::ResourceManager> resmgr;
    mem::Rc<GuiWrapper> gui;
    mem::Rc<Settings> settings;
    mem::Rc<AudioPlayer> audioPlayer;

    static inline const sf::FloatRect FULLSCREEN_VIEWPORT = {
        0.f, 0.f, 1.f, 1.f
    };
    const sf::Vector2f GAME_RESOLUTION;

    Scene scene;
    AudioEngine audioEngine;
    GameRulesEngine gameRulesEngine;
    PhysicsEngine physicsEngine;
    RenderingEngine renderingEngine;
};