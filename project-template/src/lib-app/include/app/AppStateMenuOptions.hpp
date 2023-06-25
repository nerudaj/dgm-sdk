#pragma once

#include "GuiState.hpp"
#include "Settings.hpp"

class AppStateMenuOptions final
    : public dgm::AppState
    , public GuiState
{
protected:
    Settings& settings;

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

    [[nodiscard]] AppStateMenuOptions(
        dgm::App& app,
        std::shared_ptr<GuiWrapper> gui,
        AudioPlayer& audioPlayer,
        Settings& settings)
        : dgm::AppState(app), GuiState(gui, audioPlayer), settings(settings)
    {
        buildLayout();
    }
};