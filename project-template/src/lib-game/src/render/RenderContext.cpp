#include "render/RenderContext.hpp"

template<dgm::UniversalReference<sf::Color> _Color>
[[nodiscard]] static sf::Text
createTextObject(const sf::Font& font, unsigned charSize, _Color&& color)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setFillColor(std::forward<_Color>(color));
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