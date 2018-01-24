
#include "catch.hpp"

#include <algorithm.hpp>
#include <array.hpp>

using namespace pstd;

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
    array<int, 6> a = {1, 2, 3, 4, 5, 6};
    array<int, 6> b = {1, 2, 3, 6, 5, 6};

    auto mm = mismatch(begin(a), end(a), begin(b), end(b));
    REQUIRE(mm.first == begin(a) + 3);
    REQUIRE(mm.second == begin(b) + 3);
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
    auto pred = [](int i){return i > 4};
    REQUIRE(find_if(begin(a), end(a), pred) == begin(a) + 5);
}
TEST_CASE("find_end", "[algorithm]")
{

}
TEST_CASE("find_first_of", "[algorithm]")
{
}
TEST_CASE("ajacent_find", "[algorithm]")
{
}
TEST_CASE("copy", "[algorithm]")
{
}
TEST_CASE("copy_if", "[algorithm]")
{
}
TEST_CASE("copy_n", "[algorithm]")
{
}
TEST_CASE("copy_backward", "[algorithm]")
{
}
TEST_CASE("move", "[algorithm]")
{
}
TEST_CASE("move_backward", "[algorithm]")
{
}
TEST_CASE("fill", "[algorithm]")
{
}
TEST_CASE("fill_n", "[algorithm]")
{
}
TEST_CASE("transform", "[algorithm]")
{
}
TEST_CASE("generate", "[algorithm]")
{
}
TEST_CASE("remove", "[algorithm]")
{
}
TEST_CASE("remove_if", "[algorithm]")
{
}
TEST_CASE("remove_copy", "[algorithm]")
{
}
TEST_CASE("replace", "[algorithm]")
{
}
TEST_CASE("replace_if", "[algorithm]")
{
}
TEST_CASE("replace_copy", "[algorithm]")
{
}
TEST_CASE("replace_copy_if", "[algorithm]")
{
}
TEST_CASE("swap_ranges", "[algorithm]")
{
}
TEST_CASE("iter_swap", "[algorithm]")
{
}
TEST_CASE("reverse", "[algorithm]")
{
}
TEST_CASE("reverse_copy", "[algorithm]")
{
}
TEST_CASE("rotate", "[algorithm]")
{
}
TEST_CASE("rotate_copy", "[algorithm]")
{
}
TEST_CASE("unique", "[algorithm]")
{
}
TEST_CASE("unique_copy", "[algorithm]")
{
}
TEST_CASE("is_partitioned", "[algorithm]")
{
}
TEST_CASE("partition", "[algorithm]")
{
}
TEST_CASE("partition_copy", "[algorithm]")
{
}
TEST_CASE("stable_partition", "[algorithm]")
{
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
}
TEST_CASE("min", "[algorithm]")
{
}
TEST_CASE("max_element", "[algorithm]")
{
}
TEST_CASE("min_element", "[algorithm]")
{
}
TEST_CASE("minmax", "[algorithm]")
{
}
TEST_CASE("minmax_element", "[algorithm]")
{
}
TEST_CASE("lexographical_compare", "[algorithm]")
{
}
