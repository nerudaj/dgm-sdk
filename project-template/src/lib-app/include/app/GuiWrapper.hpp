#pragma once

#include <DGM/dgm.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

class GuiWrapper
{
public:
    [[nodiscard]] explicit GuiWrapper(sf::RenderWindow& window)
    {
        gui.setTarget(window);
    }

public:
    [[nodiscard]] constexpr inline tgui::Gui& get() noexcept
    {
        return gui;
    }

    [[nodiscard]] constexpr inline const tgui::Gui& get() const noexcept
    {
        return gui;
    }

    [[nodiscard]] inline dgm::ResourceManager::LoadCallback<tgui::Font>
    getFontLoadCallback() const noexcept
    {
        return [](const std::filesystem::path& path, tgui::Font& font)
        { font = tgui::Font(path.string()); };
    };

private:
    tgui::Gui gui;
};
