#pragma once

#include <string>
#include <variant>

// Add dedicated structure for each event
struct EventPlaySound
{
	std::string name = "";
	unsigned channel = 0;
	bool force = false;
};

// Add each new type to variant template
typedef std::variant<
	EventPlaySound
	//, EventSomething...
> EventType;


