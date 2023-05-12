#include "app/AppStateMainMenu.hpp"
#include "app/AppStateIngame.hpp"
#include "app/AppStateMenuOptions.hpp"
#include "settings/GameTitle.hpp"

void AppStateMainMenu::buildLayout()
{
    auto title =
        createWindowTitle({ "0%", "5%" }, { "100%", "25%" }, GAME_TITLE);
    title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    title->setTextSize(72);
    gui.add(title);

    auto layout = tgui::VerticalLayout::create({ "15%", "30%" });
    layout->setPosition("42.5%", "35%");
    gui.add(layout);

    createButtonListInLayout(
        layout,
        { ButtonProps(
              "Play",
              [this]() {
                  app.pushState<AppStateIngame>(resmgr, settings, audioPlayer);
              }),
          ButtonProps(
              "Options",
              [this]() {
                  app.pushState<AppStateMenuOptions>(
                      resmgr, audioPlayer, settings);
              }),
          ButtonProps("Exit", [this]() { app.exit(); }) },
        0.05f);
}

void AppStateMainMenu::input()
{
    if (settings.cmdSettings.skipMainMenu)
    {
        app.pushState<AppStateIngame>(resmgr, settings, audioPlayer);
        settings.cmdSettings.skipMainMenu = false;
    }

    sf::Event event;
    while (app.window.pollEvent(event))
    {
        gui.handleEvent(event);
    }
}

AppStateMainMenu::AppStateMainMenu(
    dgm::App& app,
    const dgm::ResourceManager& resmgr,
    AudioPlayer& audioPlayer,
    Settings& settings)
    : dgm::AppState(app), GuiState(resmgr, audioPlayer), settings(settings)
{
    gui.setTarget(app.window.getWindowContext());
    buildLayout();
}