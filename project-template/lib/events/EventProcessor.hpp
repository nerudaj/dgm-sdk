#pragma once

#include <core/AudioPlayer.hpp>
#include <game/EntityTable.hpp>
#include <events/Events.hpp>

class EventProcessor
{
public:
	EventProcessor(
		AudioPlayer& ap,
		EntityTable& et) noexcept
		: audioPlayer(ap)
		, entityTable(et)
	{}

public:
	void operator()(const EventPlaySound& e);

	// Add operator() overloads for each new type

protected:
	AudioPlayer& audioPlayer;
	EntityTable& entityTable;
};
