#include "Game.hpp"
#include <events/EventQueue.hpp>

Game::Game(
		dgm::Camera& camera)
	: camera(camera)
{}

void Game::update(const dgm::Time& time)
{
	fpsCounter.update(time.getDeltaTime());
	camera.update(time);
}
