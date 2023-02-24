#include "Renderer.hpp"

Renderer::Renderer(
		dgm::ResourceManager const& resmgr,
	Game const& game)
	: resmgr(resmgr)
	, game(game)
{
	// Setup text
	fpsDisplayText.setFont(resmgr.get<sf::Font>("cruft.ttf"));
	fpsDisplayText.setFillColor(sf::Color::White);
	fpsDisplayText.setOutlineColor(sf::Color::Black);
	fpsDisplayText.setOutlineThickness(1.f);
	fpsDisplayText.setCharacterSize(60);
	fpsDisplayText.setPosition({ 20, 20 });
}

void Renderer::renderWorldTo(dgm::Window& window)
{}

void Renderer::renderHudTo(dgm::Window& window)
{
	fpsDisplayText.setString(game.getFpsCounter().getText());
	window.draw(fpsDisplayText);
}
