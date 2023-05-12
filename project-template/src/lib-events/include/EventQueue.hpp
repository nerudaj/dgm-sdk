#pragma once

#include "AudioEvents.hpp"
#include "GameRuleEvents.hpp"
#include "PhysicsEvents.hpp"
#include "RenderingEvents.hpp"
#include <vector>

class EventQueue final
{
public:
    /// <summary>
    /// Push new event into event queue. Event will be automatically
    /// placed into appropriate variant vector;
    /// </summary>
    /// <typeparam name="T">Type of event</typeparam>
    /// <typeparam name="...Args">Arguments for the construction of
    /// event</typeparam> <param name="...args"></param>
    template<class T, class... Args>
    constexpr void add(Args&&... args)
    {
        if constexpr (isTypeInVariant<T>(audioEvents))
        {
            audioEvents.emplace_back<T>(std::forward<Args>(args)...);
        }
        else if constexpr (isTypeInVariant<T>(gameEvents))
        {
            gameEvents.emplace_back<T>(std::forward<Args>(args)...);
        }
        else if constexpr (isTypeInVariant<T>(physicsEvents))
        {
            physicsEvents.emplace_back<T>(std::forward<Args>(args)...);
        }
        else if constexpr (isTypeInVariant<T>(renderingEvents))
        {
            renderingEvents.emplace_back<T>(std::forward<Args>(args)...);
        }
    }

    template<class EventType, class Visitor>
    constexpr void processEvents(Visitor& visitor)
    {
        if constexpr (std::is_same_v<EventType, AudioEvent>)
        {
            std::visit(visitor, audioEvents);
            audioEvents.clear();
        }
        else if constexpr (std::is_same_v<EventType, GameEvent>)
        {
            std::visit(visitor, gameEvents);
            gameEvents.clear();
        }
        else if constexpr (std::is_same_v<EventType, PhysicsEvent>)
        {
            std::visit(visitor, physicsEvents);
            physicsEvents.clear();
        }
        else if constexpr (std::is_same_v<EventType, RenderingEvent>)
        {
            std::visit(visitor, renderingEvents);
            renderingEvents.clear();
        }
    }

private:
    template<class T, class... Ts>
    consteval bool isTypeInVariant(const std::variant<Ts...>& v)
    {
        return std::disjunction_v<std::is_same<T, Ts>...>;
    }

    std::vector<AudioEvent> audioEvents;
    std::vector<GameEvent> gameEvents;
    std::vector<PhysicsEvent> physicsEvents;
    std::vector<RenderingEvent> renderingEvents;
};
