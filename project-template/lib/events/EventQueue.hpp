#pragma once

#include "events/Events.hpp"
#include <vector>
#include <concepts>
#include <memory>

template<class T>
concept IsDerivedFromEventBase = std::derived_from<T, EventBase>;

/**
 *  This is a storage object for object generated each frame
 * 
 *  It is a singleton so you can easily add new events from anywhere
 *  and it contains two methods - add for adding new events like:
 *  EventQueue::add<EventPlaySound>("kick.wav, 0, false);
 * 
 *  and a function process for dealing with the whole queue using
 *  some EventProcessor. Once the whole queue is processed, all
 *  events are deleted.
 */
class EventQueue {
protected:
	std::vector<std::unique_ptr<EventBase>> events;

	EventQueue() = default;
	static EventQueue& get() noexcept {
		static EventQueue instance;
		return instance;
	}

public:
	static void process(EventProcessor& p) {
		for (auto&& e : get().events)
			e->apply(p);
		get().events.clear();
	}
	
	/**
	 *  Add new event to the queue
	 * 
	 *  Event will be processed next time you issue call to process
	 *  Event must derive from EventBase and must be constructible
	 *  from parameters passed to a function.
	 */
	template<IsDerivedFromEventBase T, class ... Args>
	requires std::constructible_from<T, Args...>
	static void add(Args&& ... args) {
		get().events.push_back(std::make_unique<T>(args...));
	}
};