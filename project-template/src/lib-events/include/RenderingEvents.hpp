#pragma once

#include <variant>

struct DummyRenderingEvent
{};

using RenderingEvent = std::variant<DummyRenderingEvent>;
