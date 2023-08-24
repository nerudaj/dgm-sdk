#include "render/RenderContext.hpp"

[[nodiscard]] static sf::Text createTextObject(
    const sf::Font& font,
    unsigned charSize,
    dgm::UniversalReference<sf::Color> auto&& color)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setFillColor(std::forward<decltype(color)>(color));
    return text;
};

RenderContext
RenderContext::buildRenderContext(const dgm::ResourceManager& resmgr)
{
    return RenderContext {
        .text = createTextObject(
            resmgr.get<sf::Font>("cruft.ttf").value(), 32u, sf::Color::White)
    };
}