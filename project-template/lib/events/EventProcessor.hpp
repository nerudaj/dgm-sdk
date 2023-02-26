#pragma once

#include <events/Events.hpp>
#include <core/AudioPlayer.hpp>
#include <game/Game.hpp>
#include <game/Renderer.hpp>
#include <DGM/classes/App.hpp>

/**
 * Class providing implementation handlers for events.
 *
 * It uses std::visit and thus each event needs to overload
 * the operator(). Processor has access to the game object
 * renderer and dgm::App, so it can be used to manipulate
 * animation engine in the renderer from the game or
 * it can be used to fire up a new game state (for example
 * when player triggers an unlock minigame).
 */
class EventProcessor
{
public:
	EventProcessor(
		AudioPlayer& ap,
		Game& g,
		Renderer& r,
		dgm::App& app) noexcept
		: audioPlayer(ap)
		, game(g)
		, renderer(r)
		, app(app)
	{}

public:
	void operator()(const EventPlaySound& e);

	// Add operator() overloads for each new type

protected:
	AudioPlayer& audioPlayer;
	Game& game;
	Renderer& renderer;
	dgm::App& app;
};
