#pragma once

#include <string>
#include "game/EntityTable.hpp"

// Add forward declaration for each new event
struct EventBase;
struct EventPlaySound;

// -------------------------------------------
// Add declaration for a process method for each new event

/**
 *  Class responsible for dealing with events
 * 
 *  This class uses a double-dispatch pattern that is handled
 *  by EventQueue class.
 * 
 *  Queue applies this processor to each event in the queue.
 *  This in return calls the proper overload of process method
 *  for a concrete event class so you can handle the associated
 *  action.
 */
class EventProcessor {
protected:
	EntityTable& entityTable;

public:
	void process(EventPlaySound& e);

	EventProcessor(EntityTable& ep) : entityTable(ep) {}
};

// -------------------------------------------

struct EventBase {
	virtual void apply(EventProcessor& p) = 0;
	virtual ~EventBase() = default;
};

#define EVENT_APPLY_OVERRIDE virtual void apply(EventProcessor& p) override { p.process(*this); }

struct EventPlaySound : public EventBase {
	std::string name = "";
	unsigned channel = 0;
	bool force = false;

	EVENT_APPLY_OVERRIDE;
	EventPlaySound(std::string&& n, unsigned c, bool f) : name(n), channel(c), force(f) {}
};

// Define the new event class here. Always inherit EventBase
// and use EVENT_APPLY_OVERRIDE macro
