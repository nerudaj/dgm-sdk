#include <catch.hpp>
#include <events/EventQueue.hpp>
#include <events/GameRuleEvents.hpp>

struct TestVisitor
{
    void reset()
    {
        generateNewEventOnFirstVisit = true;
        visitedCount = 0;
    }

    void operator()(const DummyGameEvent& e)
    {
        if (generateNewEventOnFirstVisit)
        {
            generateNewEventOnFirstVisit = false;
            EventQueue::add<DummyGameEvent>(DummyGameEvent {});
        }
        ++visitedCount;
    }

    bool generateNewEventOnFirstVisit = true;
    unsigned visitedCount = 0;
};

TEST_CASE("[EventQueue]")
{
    SECTION("Correctly visits events that generate other events")
    {
        EventQueue::add<DummyGameEvent>(DummyGameEvent {});
        TestVisitor visitor;
        EventQueue::processEvents<GameEvent>(visitor);
        REQUIRE(visitor.visitedCount == 2u);
    }
}