#pragma once

#include "GuiState.hpp"
#include "Settings.hpp"

class AppStateMainMenu final
    : public dgm::AppState
    , public GuiState
{
private:
    void buildLayoutImpl() override;

public:
    virtual void input() override;

    virtual void update() override {}

    virtual void draw() override
    {
        gui->get().draw();
    }

    virtual [[nodiscard]] bool isTransparent() const noexcept override
    {
        return false;
    }

    virtual [[nodiscard]] sf::Color getClearColor() const override
    {
        return sf::Color::White;
    }

    virtual void restoreFocus() override
    {
        GuiState::restoreFocus(app.window.getWindowContext());
    }

    [[nodiscard]] AppStateMainMenu(
        dgm::App& app,
        const dgm::ResourceManager& resmgr,
        std::shared_ptr<GuiWrapper> gui,
        AudioPlayer& audioPlayer,
        Settings& settings)
        : dgm::AppState(app)
        , GuiState(gui, audioPlayer)
        , settings(settings)
        , resmgr(resmgr)
    {
        buildLayout();
    }

private:
    Settings& settings;
    const dgm::ResourceManager& resmgr;
};