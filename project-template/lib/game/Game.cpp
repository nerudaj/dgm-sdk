#include "Game.hpp"
#include <events/EventQueue.hpp>

Game::Game(
		dgm::Camera& camera,
		AudioPlayer& audioPlayer)
	: audioPlayer(audioPlayer)
	, camera(camera)
{}

void Game::update(const dgm::Time& time)
{
	fpsCounter.update(time.getDeltaTime());
	camera.update(time);

	// At the end of each update, process the event queue
	EventQueue::process(eventProcessor);
}
