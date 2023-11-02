#pragma once

#include <utils/Multiqueue.hpp>
#include <events/GameRuleEvents.hpp>
#include <events/RenderingEvents.hpp>

using EventQueue = Multiqueue<GameEvent, RenderingEvent>;
