#include "Events.hpp"

void EventProcessor::process(EventPlaySound& e) {
	entityTable.audioPlayer.playSoundOnChannel(e.name, e.channel, e.force);
}
