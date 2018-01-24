
#include <utility.hpp>
#include "catch.hpp"
TEST_CASE("swap", "[utility]")
{
    GIVEN("two integers")
    {
        int a = 10;
        int b = 20;
        WHEN("the integers are swapped")
        {
            pstd::swap(a, b);
            THEN("values should be swapped")
            {
                REQUIRE(a == 20);
                REQUIRE(b == 10);
            }
        }
    }
}

TEST_CASE("pair", "[utility]")
{
    pstd::pair<int, int> p1{1, 2};
    REQUIRE(pstd::get<0>(p1) == 1);
    REQUIRE(pstd::get<1>(p1) == 2);

    pstd::pair<int, int> p2(p1);
    REQUIRE(pstd::get<0>(p2) == 1);
    REQUIRE(pstd::get<1>(p2) == 2);

    pstd::pair<int, int> p3 = p1;
    REQUIRE(pstd::get<0>(p3) == 1);
    REQUIRE(pstd::get<1>(p3) == 2);

    pstd::pair<int, int> p4;
    p4 = p1;
    REQUIRE(pstd::get<0>(p4) == 1);
    REQUIRE(pstd::get<1>(p4) == 2);

}
