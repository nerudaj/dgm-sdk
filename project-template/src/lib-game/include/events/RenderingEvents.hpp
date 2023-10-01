#pragma once

#include <variant>

struct EventToggleFpsRequested
{
};

using RenderingEvent = std::variant<EventToggleFpsRequested>;
