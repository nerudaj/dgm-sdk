#pragma once

#include <string>
#include <variant>
#include "game/EntityTable.hpp"

// Add dedicated structure for each event
struct EventPlaySound {
	std::string name = "";
	unsigned channel = 0;
	bool force = false;
};

// Add each new type to variant template
typedef std::variant<
	EventPlaySound
	//, EventSomething...
> EventType;

class EventProcessor {
protected:
	EntityTable& entityTable;

public:
	void operator()(const EventPlaySound& e);

	// Add operator() overloads for each new type

	EventProcessor(EntityTable& et) : entityTable(et) {}
};
