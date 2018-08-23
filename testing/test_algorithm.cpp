
#include "catch.hpp"

#include <algorithm.hpp>
#include <array.hpp>

using namespace pstd;

namespace pstd
{
    template<typename T, size_t N>
    static std::ostream& operator<<(std::ostream& os, array<T, N> const& arr)
    {
        os << "[";
        for(size_t i = 0; i < N-1; i++)
        {
            os << arr[i] << ", ";
        }
        os << arr[N-1] << "]";
        return os;
    }
}



namespace
{
    template<typename T, size_t N>
    array<T, N> random_array()
    {
        array<T, N> out;
        for(auto& i: out)
        {
            i = static_cast<T>(rand());
        }
        return out;
    }


}

TEST_CASE("all_of", "[algorithm]")
{
    array<int, 5> a = {1, 1, 1, 1, 1};
    array<int, 5> b = {1, 1, 2, 1, 1};
    auto comp = [](int i){return (i & 1) == 1;}; //odd

    REQUIRE(all_of(begin(a), end(a), comp) == true);
    REQUIRE(all_of(begin(b), end(b), comp) == false);

}
TEST_CASE("any_of", "[algorithm]")
{
    array<int, 5> a = {1, 1, 1, 1, 1};
    array<int, 5> b = {1, 1, 2, 1, 1};
    auto comp = [](int i){return (i & 1) == 0;}; //even
    REQUIRE(any_of(begin(a), end(a), comp) == false);
    REQUIRE(any_of(begin(b), end(b), comp) == true);
}
TEST_CASE("none_of", "[algorithm]")
{
    array<int, 5> a = {1, 1, 1, 1, 1};
    array<int, 5> b = {1, 1, 2, 1, 1};
    auto comp = [](int i){return (i & 1) == 0;}; //even
    REQUIRE(none_of(begin(a), end(a), comp) == true);
    REQUIRE(none_of(begin(b), end(b), comp) == false);
}
TEST_CASE("for_each", "[algorithm]")
{
    array<int, 5> a = {1, 2, 3, 4, 5};
    auto op = [](int& a) {a = a*2;};

    for_each(begin(a), end(a), op);
    array<int, 5> b = {2, 4, 6, 8, 10};

    REQUIRE(equal(begin(a), end(a), begin(b), end(b)));
}
TEST_CASE("count", "[algorithm]")
{
    array<int, 5> a = {1, 2, 2, 2, 3};
    REQUIRE(count(begin(a), end(a), 1) == 1);
    REQUIRE(count(begin(a), end(a), 2) == 3);
    REQUIRE(count(begin(a), end(a), 3) == 1);
    REQUIRE(count(begin(a), end(a), 4) == 0);
}
TEST_CASE("count_if", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto even = [](int a){return a % 2 == 0;};
    auto odd = [&even](int a) {return not even(a);};
    REQUIRE(count_if(begin(a), end(a), even) == 5);
    REQUIRE(count_if(rbegin(a), rend(a), even) == 5);
    REQUIRE(count_if(begin(a), end(a), odd) == 5);
}
TEST_CASE("mismatch", "[algorithm]")
{
    SECTION("array mismatch")
    {
        array<int, 6> a = {1, 2, 3, 4, 5, 6};
        array<int, 6> b = {1, 2, 3, 6, 5, 6};

        auto mm = mismatch(begin(a), end(a), begin(b), end(b));
        REQUIRE(mm.first == begin(a) + 3);
        REQUIRE(mm.second == begin(b) + 3);
    }
    SECTION("a.size() < b.size()")
    {
        array<int, 6> a = {0, 1, 2, 3, 4, 5};
        array<int, 5> b = {0, 1, 2, 3, 4};

        auto mm = mismatch(begin(a), end(a), begin(b), end(b));

        REQUIRE(mm.first == begin(a) + 5);
        REQUIRE(mm.second == end(b));
    }
    SECTION("a.size() > b.size()")
    {
        array<int, 5> a = {0, 1, 2, 3, 4};
        array<int, 6> b = {0, 1, 2, 3, 4, 5};

        auto mm = mismatch(begin(a), end(a), begin(b), end(b));

        REQUIRE(mm.first == end(a));
        REQUIRE(mm.second == begin(b) + 5);
    }
    SECTION("differing sizes with mismatch")
    {
        array<int, 5> a = {0, 1, 2, 3, -1};
        array<int, 6> b = {0, 1, 2, 3, 4, 5};
        auto mm = mismatch(begin(a), end(a), begin(b), end(b));

        REQUIRE(mm.first == begin(a)+4);
        REQUIRE(mm.second == begin(b)+4);
        REQUIRE(*mm.first == -1);
        REQUIRE(*mm.second == 4);
    }

    SECTION("both empty")
    {
        array<int, 0> a = {};
        array<int, 0> b = {};
        REQUIRE(begin(a) == end(a));
        REQUIRE(begin(b) == end(b));

        auto mm = mismatch(begin(a), end(a), begin(b), end(b));
        REQUIRE(mm.first == end(a));
        REQUIRE(mm.second == end(b));
    }
    SECTION("One empty")
    {
        array<int, 5> a = {0, 1, 2, 3, 4};
        array<int, 0> b = {};

        auto mm1 = mismatch(begin(a), end(a), begin(b), end(b));
        auto mm2 = mismatch(begin(b), end(b), begin(a), end(a));

        REQUIRE(mm1.first == begin(a));
        REQUIRE(mm1.second == end(b));

        REQUIRE(mm2.first == end(b));
        REQUIRE(mm2.second == begin(a));
    }

}
TEST_CASE("equal", "[algorithm]")
{
    array<int, 5> a = {1, 2, 3, 4, 5};
    array<int, 5> b = {1, 2, 5, 4, 5};
    REQUIRE(equal(begin(a), end(a), begin(a)) == true);
    REQUIRE(equal(begin(a), end(a), begin(a), end(a)) == true);
    REQUIRE(equal(begin(a), end(a), begin(b)) == false);
    REQUIRE(equal(begin(a), end(a), begin(b), end(b)) == false);
    array<int, 4> s = {1, 2, 3, 4};
    REQUIRE(equal(begin(s), end(s), begin(a)) == true);
    REQUIRE(equal(begin(s), end(s), begin(a), end(a)) == false);
}
TEST_CASE("find", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    REQUIRE(find(begin(a), end(a), 2) == begin(a) + 2);
    REQUIRE(find(begin(a), end(a), 4) == begin(a) + 4);
    REQUIRE(find(begin(a), end(a), 5) == begin(a) + 5);
    REQUIRE(find(begin(a), end(a), 7) == begin(a) + 7);
    REQUIRE(find(begin(a), end(a), 9) == begin(a) + 9);
    REQUIRE(find(begin(a), end(a), 10) == end(a));
}
TEST_CASE("find_if", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto pred = [](int i){return i > 4;};
    REQUIRE(find_if(begin(a), end(a), pred) == begin(a) + 5);
}
TEST_CASE("find_end", "[algorithm]")
{
    array<int, 10> a = {0,1,2,3,4,5,6,1,2,9};

    SECTION("single match")
    {
        array<int, 3> b = {1,2,3};
        // finds first
        REQUIRE(find_end(begin(a), end(a), begin(b), end(b)) == begin(a) + 1);
    }
    SECTION("Multiple matches")
    {
        array<int, 2> b = {1, 2};
        //finds second.
        auto ret = find_end(begin(a), end(a), begin(b), end(b));
        REQUIRE(ret != end(a));
        REQUIRE(distance(begin(a), ret) == 7);
    }
    SECTION("No matches")
    {
        //not found
        array<int, 3> c = {9,9,9};
        REQUIRE(find_end(begin(a), end(a), begin(c), end(c)) == end(a));
        array<int, 10> d = {1, 2, 4, 5, 6, 7, 8, 9, 0, 0};
        REQUIRE(find_end(begin(d), end(d), begin(c), end(c)) == end(d));
    }


}
TEST_CASE("find_first_of", "[algorithm]")
{
    array<int, 10> a = {0,1,2,3,4,5,6,7,8,9};
    REQUIRE(find_first_of(begin(a), end(a), begin(a), end(a)) == begin(a));
    array<int, 3> b = {7, 6, 5};
    REQUIRE(find_first_of(begin(a), end(a), begin(b), end(b)) == begin(a) + 5);
    array<int, 3> c = {10, 11, 12};
    REQUIRE(find_first_of(begin(a), end(a), begin(c), end(c)) == end(a));
}
TEST_CASE("ajacent_find", "[algorithm]")
{
    SECTION("ajacent elements")
    {
        array<int, 10> a = {0,1,2,3,3,5,6,7,8,9};
        REQUIRE(ajacent_find(begin(a), end(a)) == begin(a) + 3);
    }
    SECTION("no ajacent elements")
    {
        array<int, 10> b = {0,1,2,3,4,5,6,7,8,9};
        auto ret = ajacent_find(begin(b), end(b));
        REQUIRE(ret == end(b));
    }
}
TEST_CASE("copy", "[algorithm]")
{
    array<int, 10> a = {0,1,2,3,4,5,6,7,8,9};
    array<int, 10> b = {0,0,0,0,0,0,0,0,0,0};
    REQUIRE(copy(begin(a), end(a), begin(b)) == end(b));
    for(size_t i = 0; i < b.size(); i++)
    {
        REQUIRE(b[i] == i);
    }
}
TEST_CASE("copy_if", "[algorithm]")
{
    array<int, 10> a = {0,1,2,3,4,5,6,7,8,9};
    array<int, 10> b = {0,0,0,0,0,0,0,0,0,0};
    REQUIRE(copy_if(begin(a), end(a), begin(b), [](int i){return (i % 2)==0;}) == begin(b) + 5);
    for(size_t i = 0; i < 5; i++)
    {REQUIRE(b[i] == 2*i);}
}
TEST_CASE("copy_n", "[algorithm]")
{
    array<int, 10> a = {0,1,2,3,4,5,6,7,8,9};
    array<int, 10> b = {0,0,0,0,0,0,0,0,0,0};
    REQUIRE(copy_n(begin(a), b.size(), begin(b)) == end(b));
    for(size_t i = 0; i < b.size(); i++)
    {
        REQUIRE(b[i] == i);
    }
}
TEST_CASE("copy_backward", "[algorithm]")
{
    array<int, 10> a = {0,1,2,3,4,5,6,7,8,9};
    array<int, 10> b = {0,0,0,0,0,0,0,0,0,0};
    REQUIRE(copy_backward(begin(a), end(a), end(b)) == begin(b));
    for(size_t i = 0; i < b.size(); i++)
    {
        REQUIRE(b[i] == i);
    }
}
TEST_CASE("move", "[algorithm]")
{
    array<int, 10> a = {0,1,2,3,4,5,6,7,8,9};
    array<int, 10> b = {0,0,0,0,0,0,0,0,0,0};
    REQUIRE(move(begin(a), end(a), begin(b)) == end(b));
    for(size_t i = 0; i < b.size(); i++)
    {
        REQUIRE(b[i] == i);
    }
}
TEST_CASE("move_backward", "[algorithm]")
{
    array<int, 10> a = {0,1,2,3,4,5,6,7,8,9};
    array<int, 10> b = {0,0,0,0,0,0,0,0,0,0};
    REQUIRE(move_backward(begin(a), end(a), end(b)) == begin(b));
    for(size_t i = 0; i < b.size(); i++)
    {
        REQUIRE(b[i] == i);
    }
}
TEST_CASE("fill", "[algorithm]")
{
    array<int, 10> b = {0,0,0,0,0,0,0,0,0,0};
    fill(begin(b), end(b), 3);
    for(auto i: b)
    {
        REQUIRE(i == 3);
    }
}
TEST_CASE("fill_n", "[algorithm]")
{
    array<int, 10> b = {0,0,0,0,0,0,0,0,0,0};
    fill_n(begin(b), 5, 3);
    for(size_t i = 0; i < 10; i++)
    {
        if(i < 5) REQUIRE(b[i] == 3);
        else REQUIRE(b[i] == 0);
    }
}
TEST_CASE("transform", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    array<int, 10> b = {};
    array<int, 10> c = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
    REQUIRE(transform(begin(a), end(a), begin(b), [](int i){return 2*i;}) == end(b));
    for(size_t i = 0; i < 10; i++)
    {
        REQUIRE(b[i] == c[i]);
    }
}
TEST_CASE("generate", "[algorithm]")
{
    array<int, 10> b = {};
    int n = 0;
    generate(begin(b), end(b), [&n](){return n++;});
    for(size_t i = 0; i < 10; i++)
    {
        REQUIRE(b[i] == i);
    }
    n = 0;
    generate(begin(b), end(b), [&n](){return 2*n++;});
    for(size_t i = 0; i < 10; i++)
    {
        REQUIRE(b[i] == 2*i);
    }
}
TEST_CASE("remove_if", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto even = [](int i){return (i%2)==0;};
    auto it = remove_if(begin(a), end(a), even);
    REQUIRE(it == begin(a) + 5);
    for(size_t i = 0; i < 5; i++)
    {
        REQUIRE(even(a[i]) == false);
        REQUIRE(a[i] == 2*i+1);
    }
}

TEST_CASE("remove_copy_if", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    array<int, 10> b = {};
    for(int i: b) REQUIRE(i == 0);
    auto even = [](int i){return (i%2)== 0;};

    auto it = remove_copy_if(begin(a), end(a), begin(b), even);
    REQUIRE(it == begin(b)+5);

    for(size_t i = 0; i < 5; i++)
    {
        INFO("i=" << i);
        REQUIRE(even(b[i]) == false);
    }
    for(size_t i = 5; i < 10; i++)
    {
        INFO("i=" << i);
        REQUIRE(b[i] == 0);
    }
}

TEST_CASE("remove_copy", "[algorithm]")
{
    array<int, 20> a = {0, -1, 1, -1, 2, -1, 3, -1, 4, -1, 5, -1, 6, -1, 7, -1, 8, -1, 9, -1};
    array<int, 20> b = {};
    auto it = remove_copy(begin(a), end(a), begin(b), -1);

    REQUIRE(it == begin(b)+10);

    for(int i = 0; i < 10; i++)
    {
        REQUIRE(b[i] == i);
    }
    for(int i = 10; i < 20; i++)
    {
        REQUIRE(b[i] == 0);
    }
}

TEST_CASE("replace", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   SECTION("replace 0")
   {
       replace(begin(a), end(a), 0, -1);

       REQUIRE(a[0] == -1);
       for(size_t i = 1; i < a.size(); i++)
       {
           INFO("i==" << i);
           REQUIRE(a[i] == i);
       }
   }
   SECTION("replace 10")
   {
       replace(begin(a), end(a), 10, -1);
       for(size_t i = 0; i < 10; i++)
       {
           INFO("i == " << i);
           REQUIRE(a[i] == i);
       }
   }
   SECTION("replace 5")
   {
       replace(begin(a), end(a), 5, -1);

       for(size_t i = 0; i < 10; i++)
       {
           if(i == 5)
           {
               REQUIRE(a[i] == -1);
           }
           else
           {
               REQUIRE(a[i] == i);
           }
       }
   }
}

TEST_CASE("replace_if", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    SECTION("remove even")
    {
        auto even = [](int i){return (i%2)== 0;};
        replace_if(begin(a), end(a), even, -1);

        for(size_t i = 0; i < 10; i++)
        {
            if(even(i))
            {
                REQUIRE(a[i] == -1);
            }
            else
            {
                REQUIRE(a[i] == i);
            }
        }
    }
}

TEST_CASE("replace_copy", "[algorithm]")
{
    array<int, 10> source = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    array<int, 10> dest = {};

    SECTION("replace value")
    {
        auto ret = replace_copy(begin(source), end(source), begin(dest), 3, -1);

        REQUIRE(ret == end(dest));

        for(size_t i = 0; i < 10; i++)
        {
             if(i == 3)
             {
                 REQUIRE(dest[i] == -1);
             }
             else
             {
                 REQUIRE(dest[i] == source[i]);
             }
        }
    }

    SECTION("replace nothing")
    {
        auto ret = replace_copy(begin(source), end(source), begin(dest), 100, -1);
        REQUIRE(ret == end(dest));
        for(size_t i = 0; i < 10; i++)
        {
            REQUIRE(source[i] == dest[i]);
        }
    }


}

TEST_CASE("replace_copy_if", "[algorithm]")
{
    array<int, 10> source = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    array<int, 10> dest = {};

    SECTION("replace evens")
    {
        auto even = [](int i){return (i&1) != 0;};
        auto ret = replace_copy_if(begin(source), end(source), begin(dest), even, -1);
        REQUIRE(ret == end(dest));

        for(size_t i = 0; i < 10; i++)
        {
            if(even(i))
            {
                REQUIRE(dest[i] == -1);
            }
            else
            {
                REQUIRE(dest[i] == source[i]);
            }
        }
    }

}

TEST_CASE("swap_ranges", "[algorithm]")
{
    array<int, 10> positive = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    array<int, 10> negative = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};

    auto ret = swap_ranges(begin(positive), end(positive), begin(negative));

    REQUIRE(ret == end(negative));

    for(size_t i = 0; i < 10; i++)
    {
        INFO(i);
        REQUIRE(positive[i] == -1 * negative[i]);
        REQUIRE(positive[i] < 0);
        REQUIRE(negative[i] > 0);
    }
}

TEST_CASE("iter_swap", "[algorithm]")
{
    int a = 10;
    int b = 42;

    iter_swap(&a, &b);

    REQUIRE(a == 42);
    REQUIRE(b == 10);

}
TEST_CASE("reverse", "[algorithm]")
{
    SECTION("reverse standard")
    {
        array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const array<int, 10> reversed = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        reverse(begin(a), end(a));

        for(size_t i = 0; i < 10; i++)
        {
            REQUIRE(a[i] == reversed[i]);
        }

    }
    SECTION("singular value")
    {
        array<int, 1> v = {1};

        reverse(begin(v), end(v));
        REQUIRE(v[0] == 1);
    }

    SECTION("two values")
    {
        array<int, 2> v = {1, 2};
        reverse(begin(v), end(v));
        REQUIRE(v[0] == 2);
        REQUIRE(v[1] == 1);
    }
    SECTION("no values")
    {
        array<int, 0> n;
        reverse(begin(n), end(n));
    }
}
TEST_CASE("reverse_copy", "[algorithm]")
{
    SECTION("range")
    {
        const array<int, 10> source = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        array<int, 10> dest = {};
        const array<int, 10> reversed = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        auto ret = reverse_copy(begin(source), end(source), begin(dest));
        REQUIRE(ret == end(dest));

        for(size_t i = 0; i < 10; i++)
        {
            REQUIRE(dest[i] == reversed[i]);
        }
    }
    SECTION("one element")
    {
        const array<int, 1> source = {1};
        array<int, 1> dest = {0};

        auto ret = reverse_copy(begin(source), end(source), begin(dest));
        REQUIRE(ret == end(dest));
        REQUIRE(dest[0] == 1);
    }
    SECTION("Two elements")
    {
        const array<int, 2> source = {1, 2};
        array<int, 2> dest = {0, 0};
        auto ret = reverse_copy(begin(source), end(source), begin(dest));
        REQUIRE(ret == end(dest));
        REQUIRE(dest[0] == 2);
        REQUIRE(dest[1] == 1);
    }
    SECTION("no elements")
    {
        array<int, 0> source = {};
        array<int, 0> dest = {};

        auto ret = reverse_copy(begin(source), end(source), begin(dest));
        REQUIRE(ret == end(dest));
    }

}
TEST_CASE("rotate", "[algorithm]")
{
    array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    SECTION("rotate nothing")
    {
        auto ret = rotate(begin(a), begin(a), end(a));
        for(int i = 0; i < 10; i++)
        {
             REQUIRE(a[i] == i);
        }
        REQUIRE(ret == begin(a));
    }
    SECTION("rotate one")
    {
        auto ret = rotate(begin(a), begin(a)+1, end(a));
        REQUIRE(ret == end(a)-1);
        const array<int, 10> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        for(int i = 0; i < 10; i++)
        {
            REQUIRE(a[i] == expected[i]);
        }
    }
    SECTION("rotate two")
    {
        auto ret = rotate(begin(a), begin(a)+2, end(a));
        REQUIRE(ret == end(a)-2);
        const array<int, 10> expected = {2, 3, 4, 5, 6, 7, 8, 9, 0, 1};
        for(int i = 0; i < 10; i++)
        {
            REQUIRE(a[i] == expected[i]);
        }
    }
}
TEST_CASE("rotate_copy", "[algorithm]")
{
    const array<int, 10> source = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    SECTION("rotate nothing")
    {
        array<int, 10> dest = {};

        auto ret = rotate_copy(begin(source), begin(source), end(source), begin(dest));
        REQUIRE(ret == end(dest));

        for(int i = 0; i < 10; i++)
        {
            REQUIRE(source[i] == dest[i]);
        }
    }
    SECTION("rotate one")
    {
        const array<int, 10> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        array<int, 10> dest = {};
        auto ret = rotate_copy(begin(source), begin(source)+1, end(source), begin(dest));

        for(int i = 0; i < 10; i++)
        {
            REQUIRE(dest[i] == expected[i]);
        }
    }
    SECTION("rotate two")
    {
        const array<int, 10> expected = {2, 3, 4, 5, 6, 7, 8, 9, 0, 1};
        array<int, 10> dest = {};
        auto ret = rotate_copy(begin(source), begin(source)+2, end(source), begin(dest));

        for(int i = 0; i < 10; i++)
        {
            REQUIRE(dest[i] == expected[i]);
        }
    }

}
TEST_CASE("unique", "[algorithm]")
{
    SECTION("already unique")
    {
        array<int, 10> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        auto ret = unique(begin(a), end(a));

        REQUIRE(ret == end(a));

        for(int i = 0; i < 10; i++)
        {
            REQUIRE(a[i] == i);
        }
    }
    SECTION("double entries")
    {
        array<int, 20> a{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};

        auto ret = unique(begin(a), end(a));
        REQUIRE(ret == begin(a)+10);

        for(int i = 0; i < 10; i++)
        {
            REQUIRE(a[i] == i);
        }
    }
    SECTION("single")
    {
        array<int, 1> a{1};
        auto ret = unique(begin(a), end(a));
        REQUIRE(ret == end(a));
        REQUIRE(a[0] == 1);
    }
    SECTION("single_repitition")
    {
        array<int, 10> a{0, 1, 2, 2, 4, 5, 6, 7, 8, 9};
        auto ret = unique(begin(a), end(a));
        REQUIRE(ret == begin(a)+9);
        REQUIRE(a[0] == 0);
        REQUIRE(a[1] == 1);
        REQUIRE(a[2] == 2);
        REQUIRE(a[3] == 4);
        REQUIRE(a[4] == 5);
        REQUIRE(a[5] == 6);
        REQUIRE(a[6] == 7);
        REQUIRE(a[7] == 8);
        REQUIRE(a[8] == 9);
    }
    SECTION("separator")
    {
        array<int, 7> a = {1, 1, 1, 2, 1, 1, 1};
        auto ret = unique(begin(a), end(a));
        REQUIRE(ret == begin(a)+3);
        REQUIRE(a[0] == 1);
        REQUIRE(a[1] == 2);
        REQUIRE(a[2] == 1);
    }
    SECTION("empty")
    {
        array<int, 0> a = {};
        auto ret = unique(begin(a), end(a));
        REQUIRE(ret == end(a));
    }
}
TEST_CASE("unique_copy", "[algorithm]")
{
    const array<int, 23> source{0, 1, 2, 3, 3, 3, 4, 5, 5, 6, 7, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 9};

    array<int, 23> dest = {};

    auto ret = unique_copy(begin(source), end(source), begin(dest));
    REQUIRE(ret == begin(dest)+10);
    for(int i = 0; i < 10; i++)
    {
        REQUIRE(dest[i] == i);
    }

}
TEST_CASE("is_partitioned", "[algorithm]")
{
    SECTION("less_than")
    {
        array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        for(int comparison = 0; comparison < 10; comparison++)
        {
            INFO("comp value == " << comparison);
            auto ret = is_partitioned(begin(a), end(a), [comparison](int i)
            {
                return i < comparison;
            });
            REQUIRE(ret == true);
        }
    }
    SECTION("empty")
    {
        array<int, 0> a{};
        auto ret = is_partitioned(begin(a), end(a), [](int i){return (i<5);});
        REQUIRE(ret == true);
    }
    SECTION("always_true")
    {
        array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto ret = is_partitioned(begin(a), end(a), [](int i){return true;});
        REQUIRE(ret == true);
    }
    SECTION("always false")
    {
        array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto ret = is_partitioned(begin(a), end(a), [](int i){return false;});
        REQUIRE(ret == true);
    }
    SECTION("bad start")
    {
        array<int, 10> a = {0, 1, 2, 7, 4, 5, 6, 7, 8, 9};

        auto ret = is_partitioned(begin(a), end(a), [](int i)
        {
            return i < 5;
        });

        REQUIRE(ret == false);
    }
    SECTION("bad end")
    {
        array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 3, 8, 9};

        auto ret = is_partitioned(begin(a), end(a), [](int i)
        {
            return i < 5;
        });
        REQUIRE(ret == false);
    }
}
TEST_CASE("partition", "[algorithm]")
{
    SECTION("Random tests")
    {
        for(int i = 0; i < 100; i++)
        {
            auto arr = random_array<int, 10>();
            INFO("array=" << arr);
            const auto partition_point = arr[0];
            const auto pred = [partition_point](int i)
            {
                return i < partition_point;
            };
            partition(begin(arr), end(arr), pred);

            REQUIRE(is_partitioned(begin(arr), end(arr), pred));
        }
    }

}
TEST_CASE("partition_copy", "[algorithm]")
{
    SECTION("Random Tests")
    {
        for(int i = 0; i < 100; i++)
        {
            const auto N_ITEMS = 10;
            auto arr = random_array<int, N_ITEMS>();
            INFO("array=" << arr);
            const auto partition_point = arr[0];
            const auto pred = [partition_point](int i)
            {
                return i < partition_point;
            };
            array<int, N_ITEMS> out_less = {};
            array<int, N_ITEMS> out_greater = {};
            auto ends = partition_copy(begin(arr), end(arr), begin(out_less), begin(out_greater), pred);
            INFO("out_true=" << out_less);
            INFO("out_false=" << out_greater);
            for(auto it = begin(out_less); it < ends.first; it++)
            {
                INFO("i=" << distance(begin(out_less), it));
                REQUIRE(*it < partition_point);
            }
            for(auto it = begin(out_greater); it < ends.second; it++)
            {
                INFO("i=" << distance(begin(out_greater), it));
                REQUIRE(*it >= partition_point);
            }

        }
    }
}

struct StableOrderable
{
    int value = 0;
    int position = 0;

    bool operator<(StableOrderable const& other) const
    {
        return this->value < other.value;
    }

    template<size_t N>
    static array<StableOrderable, N> random()
    {
        array<StableOrderable, N> arr = {};
        for(size_t i = 0; i < N; i++)
        {
            arr[i] = {rand(), static_cast<int>(i)};
        }
        return arr;
    }
};

std::ostream& operator<<(std::ostream& os, StableOrderable const& so)
{
    os << so.value << "[" << so.position << "]";
    return os;
}



TEST_CASE("stable_partition", "[algorithm]")
{
    SECTION("Random Tests")
    {
        const auto N_ITEMS = 10;
        for(int i = 0; i < 100; i++)
        {
            auto arr = StableOrderable::random<N_ITEMS>();
            INFO("Before=" << arr);
            auto const pp = arr[0];
            auto pred = [pp](StableOrderable const& so)
            {
                return so < pp;
            };
            stable_partition(begin(arr), end(arr), pred);
            INFO("After=" << arr);
            REQUIRE(is_partitioned(begin(arr), end(arr), pred));
            for(int i = 0; i < N_ITEMS-1; i++)
            {
                auto const& a = arr[i];
                auto const& b = arr[i+1];
                if(a.value == b.value) REQUIRE(a.position < b.position);
            }
        }
    }
}
TEST_CASE("partition_point", "[algorithm]")
{
}
TEST_CASE("is_sorted_until", "[algorithm]")
{
}
TEST_CASE("is_sorted", "[algorithm]")
{
}
TEST_CASE("sort", "[algorithm]")
{
}
TEST_CASE("is_heap_until", "[algorithm]")
{
}
TEST_CASE("is_heap", "[algorithm]")
{
}
TEST_CASE("push_heap", "[algorithm]")
{
}
TEST_CASE("make_heap", "[algorithm]")
{
}
TEST_CASE("pop_heap", "[algorithm]")
{
}
TEST_CASE("sort_heap", "[algorithm]")
{
}
TEST_CASE("partial_sort", "[algorithm]")
{
}
TEST_CASE("partial_sort_copy", "[algorithm]")
{
}
TEST_CASE("merge" "[algorithm]")
{
}
TEST_CASE("inplace_merge", "[algorithm]")
{
}
TEST_CASE("stable_sort", "[algorithm]")
{
}
TEST_CASE("nth_element", "[algorithm]")
{
}
TEST_CASE("lower_bound", "[algorithm]")
{
}
TEST_CASE("upper_bound", "[algorithm]")
{
}
TEST_CASE("binary_search", "[algorithm]")
{
}
TEST_CASE("equal_range", "[algorithm]")
{
}
TEST_CASE("includes", "[algorithm]")
{
}
TEST_CASE("set_difference", "[algorithm]")
{
}
TEST_CASE("set_intersection", "[algorithm]")
{
}
TEST_CASE("set_symmetric_difference", "[algorithm]")
{
}
TEST_CASE("set_union", "[algorithm]")
{
}
TEST_CASE("clamp", "[algorithm]")
{
}
TEST_CASE("max", "[algorithm]")
{
    REQUIRE(max(0, 0) == 0);
    REQUIRE(max(1, 0) == 1);
    REQUIRE(max(0, 1) == 1);
}
TEST_CASE("min", "[algorithm]")
{
    REQUIRE(min(0, 0) == 0);
    REQUIRE(min(1, 0) == 0);
    REQUIRE(min(0, 1) == 0);
}
TEST_CASE("max_element", "[algorithm]")
{
    SECTION("iota array")
    {
        const array<int, 10> arr = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
        auto it = max_element(begin(arr), end(arr));
        REQUIRE(distance(begin(arr), it) == 9);
    }
    SECTION("const_array")
    {
        const array<int, 10> arr= {{0, 0, 0, 0, 0,  0, 0, 0, 0, 0}};
        auto it = max_element(begin(arr), end(arr));
        REQUIRE(it == begin(arr));
    }
    SECTION("outlier")
    {
        const array<int, 10> arr= {{0, 0, 1, 0, 0,  0, 0, 0, 0, 0}};
        auto it = max_element(begin(arr), end(arr));
        REQUIRE(it == begin(arr)+2);
    }
    SECTION("empty")
    {
        const array<int, 0> arr = {};
        REQUIRE(max_element(begin(arr), end(arr)) == begin(arr));
    }
}
TEST_CASE("min_element", "[algorithm]")
{
    SECTION("iota array")
    {
        const array<int, 10> arr = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
        auto it = min_element(begin(arr), end(arr));
        REQUIRE(distance(begin(arr), it) == 0);
    }
    SECTION("const_array")
    {
        const array<int, 10> arr= {{0, 0, 0, 0, 0,  0, 0, 0, 0, 0}};
        auto it = min_element(begin(arr), end(arr));
        REQUIRE(it == begin(arr));
    }
    SECTION("outlier")
    {
        const array<int, 10> arr= {{0, 0, -1, 0, 0,  0, 0, 0, 0, 0}};
        auto it = min_element(begin(arr), end(arr));
        REQUIRE(it == begin(arr)+2);
    }
    SECTION("empty")
    {
        const array<int, 0> arr = {};
        REQUIRE(min_element(begin(arr), end(arr)) == begin(arr));
    }
}
TEST_CASE("minmax", "[algorithm]")
{
    auto t1 = minmax(0, 0);
    REQUIRE(t1.first == 0);
    REQUIRE(t1.second == 0);

    auto t2 = minmax(0, 1);
    REQUIRE(t2.first == 0);
    REQUIRE(t2.second == 1);

    auto t3 = minmax(1, 0);
    REQUIRE(t3.first == 0);
    REQUIRE(t3.second == 1);
}
TEST_CASE("minmax_element", "[algorithm]")
{
    std::srand(0);
    SECTION("random")
    {
        for(int i = 0; i < 100; i++)
        {
            auto arr = random_array<int, 10>();

            INFO("arr=" << arr);
            auto min = min_element(begin(arr), end(arr));
            auto max =  max_element(begin(arr), end(arr));
            INFO("min=" << distance(begin(arr), min));
            INFO("*min=" << *min);
            INFO("max=" << distance(begin(arr), max));
            INFO("*max=" << *max);

            auto mm = minmax_element(begin(arr), end(arr));
            INFO("mm.first=" << distance(begin(arr), mm.first));
            INFO("*mm.first=" << *mm.first);
            INFO("mm.second=" << distance(begin(arr), mm.second));
            INFO("*mm.second=" << *mm.second);
            REQUIRE(mm.first == min);
            REQUIRE(mm.second == max);
        }

    }
}
TEST_CASE("lexographical_compare", "[algorithm]")
{
}
