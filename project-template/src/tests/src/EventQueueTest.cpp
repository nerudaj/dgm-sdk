#include <catch.hpp>
#include <events/EventQueue.hpp>
#include <variant>

struct A
{
    float f;
    char c;
};

struct B
{
};

using AB = std::variant<A, B>;

struct C
{
    int i;
};

struct D
{
};

using CD = std::variant<C, D>;

struct VisitorAB
{
    VisitorAB(EventQueue<CD, AB>& queue) : queue(queue) {}

    void operator()(A)
    {
        aVisitCnt++;
    }

    void operator()(B)
    {
        bVisitCnt++;
        queue.emplace<A>(10.f, 'a');
    }

    EventQueue<CD, AB>& queue;
    unsigned aVisitCnt = 0;
    unsigned bVisitCnt = 0;
};

TEST_CASE("[EventQueue]")
{
    SECTION("IsTypeInVariant works")
    {
        static_assert(IsTypeInVariant<A, AB>);
        static_assert(IsTypeInVariant<B, AB>);
        static_assert(!IsTypeInVariant<C, AB>);
        static_assert(!IsTypeInVariant<D, AB>);
    }

    SECTION("CanVisitVariant works")
    {
        static_assert(CanVisitVariant<VisitorAB, AB>);
        static_assert(!CanVisitVariant<VisitorAB, CD>);
    }

    SECTION("IsVariant works")
    {
        static_assert(!IsVariant<int>);
        static_assert(IsVariant<std::variant<int, float>>);
    }

    SECTION("Correctly visits events that generate other events")
    {
        EventQueue<CD, AB> queue;
        VisitorAB vis(queue);
        queue.emplace<A>(1.f, 'a');
        queue.emplace<B>();
        queue.processAndClear(vis);

        REQUIRE(vis.aVisitCnt == 2u);
        REQUIRE(vis.bVisitCnt == 1u);

        // repeated call does nothing, queue is cleared
        queue.processAndClear(vis);

        REQUIRE(vis.aVisitCnt == 2u);
        REQUIRE(vis.bVisitCnt == 1u);
    }
}