#pragma once

#include <DGM/dgm.hpp>
#include "Game.hpp"

class Renderer final
{
public:
	Renderer(
		dgm::ResourceManager const& resmgr,
		Game const& game);

public:
	void renderWorldTo(
		dgm::Window& window);

	void renderHudTo(
		dgm::Window& window);

protected:
	dgm::ResourceManager const& resmgr;
	Game const& game;

	// Render resources
	sf::Text fpsDisplayText;
};
