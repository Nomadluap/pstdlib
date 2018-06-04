#include <initializer_list.hpp>
#include "catch.hpp"
#include <array.hpp>
#include <initializer_list>
#include <array>

TEST_CASE("array", "[array]")
{
    GIVEN("an array with values")
    {
        pstd::array<int, 5> a = {0, 1, 2, 3, 4};

        static_assert(pstd::is_same<typename pstd::tuple_element<0, decltype(a)>::type, int>::value, "array is int");

        SECTION("size")
        {
            constexpr size_t sz = pstd::tuple_size<decltype(a)>::value;
            REQUIRE(sz == 5);
        }

        SECTION("operator[]")
        {
            REQUIRE(a[0] == 0);
            REQUIRE(a[1] == 1);
            REQUIRE(a[2] == 2);
            REQUIRE(a[3] == 3);
            REQUIRE(a[4] == 4);
        }

        SECTION("at()")
        {
            REQUIRE(a.at(0) == 0);
            REQUIRE(a.at(1) == 1);
            REQUIRE(a.at(2) == 2);
            REQUIRE(a.at(3) == 3);
            REQUIRE(a.at(4) == 4);
        }

        SECTION("get")
        {
            REQUIRE(pstd::get<0>(a) == 0);
            REQUIRE(pstd::get<1>(a) == 1);
            REQUIRE(pstd::get<2>(a) == 2);
            REQUIRE(pstd::get<3>(a) == 3);
            REQUIRE(pstd::get<4>(a) == 4);
        }
        SECTION("Iterators")
        {
            REQUIRE(begin(a) == a.data());
            REQUIRE(end(a) == a.data() + 5);
            REQUIRE(cbegin(a) == begin(a));
            REQUIRE(cend(a) == end(a));
        }

        SECTION("copy construction")
        {
            pstd::array<int, 5> b = a;
            REQUIRE(b[0] == 0);
            REQUIRE(b[1] == 1);
            REQUIRE(b[2] == 2);
            REQUIRE(b[3] == 3);
            REQUIRE(b[4] == 4);
        }
        SECTION("Comparison")
        {
            pstd::array<int, 5> b = a;
            REQUIRE(a == b);
            REQUIRE(a <= b);
            REQUIRE(a >= b);
            REQUIRE_FALSE(a < b);
            REQUIRE_FALSE(a > b);
            //modify the copy
            b[4] = 5;
            REQUIRE(b[4] == 5);

            REQUIRE_FALSE(a == b);
            REQUIRE(a < b);
            REQUIRE(a <= b);
            REQUIRE_FALSE(a > b);
            REQUIRE_FALSE(a >= b);

            REQUIRE(b > a);
            REQUIRE(b >= a);
            REQUIRE_FALSE(b < a);
            REQUIRE_FALSE(b <= a);
        }




    }
}

