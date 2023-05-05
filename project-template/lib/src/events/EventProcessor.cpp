#include "EventProcessor.hpp"

void EventProcessor::operator()(const EventPlaySound& e)
{
	audioPlayer.playSoundOnChannel(e.name, e.channel, e.force);
}
