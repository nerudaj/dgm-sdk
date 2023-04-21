#pragma once

#include "GuiState.hpp"
#include "core/Settings.hpp"

class AppStateMenuOptions : public dgm::AppState, public GuiState
{
protected:
    Settings& settings;

    void buildLayout();

public:
    virtual void input() override;

    virtual void update() override {}

    virtual void draw() override
    {
        gui.draw();
    }

    virtual [[nodiscard]] bool isTransparent() const noexcept override
    {
        return false;
    }

    virtual [[nodiscard]] sf::Color getClearColor() const override
    {
        return sf::Color::White;
    }

    AppStateMenuOptions(
        dgm::App& app,
        const dgm::ResourceManager& resmgr,
        AudioPlayer& audioPlayer,
        Settings& settings);
};