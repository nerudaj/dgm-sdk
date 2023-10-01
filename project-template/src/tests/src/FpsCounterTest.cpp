#include <catch.hpp>
#include <render/FpsCounter.hpp>

TEST_CASE("[FpsCounter]")
{
    SECTION("Correctly computes FPS")
    {
        FpsCounter counter;
        counter.update(0.5f);
        REQUIRE(counter.getText() == "2");
    }
}