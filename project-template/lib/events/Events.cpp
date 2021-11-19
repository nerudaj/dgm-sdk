#include "Events.hpp"

void EventProcessor::operator()(const EventPlaySound& e) {
	entityTable.audioPlayer.playSoundOnChannel(e.name, e.channel, e.force);
}
