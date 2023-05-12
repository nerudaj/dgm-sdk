#pragma once

#include "Settings.hpp"
#include "audio/AudioPlayer.hpp"
#include <DGM/dgm.hpp>

class AppStateIngame final : public dgm::AppState
{
public:
    [[nodiscard]] AppStateIngame(
        dgm::App& app,
        const dgm::ResourceManager& resmgr,
        Settings& settings,
        AudioPlayer& audioPlayer);

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
    const dgm::ResourceManager& resmgr;
    Settings& settings;
    AudioPlayer& audioPlayer;

    const sf::FloatRect FULLSCREEN_VIEWPORT = { 0.f, 0.f, 1.f, 1.f };
    const sf::Vector2f GAME_RESOLUTION;
    dgm::Camera worldCamera;
    dgm::Camera hudCamera;

    /*Game game = Game(worldCamera);
    Renderer renderer = Renderer(resmgr, game);
    EventProcessor eventProcessor =
        EventProcessor(audioPlayer, game, renderer, app);*/
};