

#include "utility.hpp"
using namespace pstd;

namespace
{
    struct A{};
    A a;
    A& aref = a;

    static_assert(is_same<decltype(move(a)), A&&>::value);
    static_assert(is_same<decltype(move(aref)), A&&>::value);

    A&& arref = move(a);

    static_assert(is_same<decltype(move(arref)), A&&>::value);

    using P = pair<int, float>;

    static_assert(is_same<tuple_element_t<0, P>, int>::value);
    static_assert(is_same<tuple_element_t<1, P>, float>::value);
    static_assert(tuple_size<P>::value == 2);

}
