#pragma once

#include <DGM/dgm.hpp>

#include <game/EntityTable.hpp>
#include <game/FpsCounter.hpp>
#include <core/AudioPlayer.hpp>
#include <events/EventProcessor.hpp>

class Game
{
public:
	Game(
		dgm::Camera& camera,
		AudioPlayer& audioPlayer);

public:
	void update(const dgm::Time& time);

	[[nodiscard]]
	constexpr auto getFpsCounter() const noexcept
		-> FpsCounter const&
	{
		return fpsCounter;
	}

protected:
	// Dependencies
	dgm::Camera& camera;
	AudioPlayer& audioPlayer;

	// Attributes
	FpsCounter fpsCounter;
	EntityTable entityTable = {};
	EventProcessor eventProcessor = EventProcessor(
		audioPlayer,
		entityTable);
};
