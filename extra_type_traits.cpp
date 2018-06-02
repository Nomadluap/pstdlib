

#include "extra_type_traits.hpp"

using namespace pstd;

namespace
{
    struct Foo
    {
        int operator()(int a, int b)
        {
            return (a+b);
        }

    };

    struct A{};

    struct ImplicitInt
    {
        operator int(){return 42;}
    };

    struct IntCtor
    {
        IntCtor(int){};
    };

    template<typename... Args>
    using is_callable_with = is_invocable_r<Args...>;

    static_assert(is_callable_with<Foo, int, int, int>::value, "Foo callable with ints");
    static_assert(is_callable_with<Foo, double, int, int>::value, "Implicit return type conversion");
    static_assert(is_callable_with<Foo, IntCtor, int, int>::value, "IMplicit return type conversion");
    static_assert(is_callable_with<Foo, int, char, char>::value, "Implicit argument conversion");
    static_assert(is_callable_with<Foo, int, int, char>::value, "Implicit argument conversion");
    static_assert(is_callable_with<Foo, int, ImplicitInt, int>::value, "implicit argument conversion");

    static_assert(not is_callable_with<Foo, int*, int, int>::value, "Does not return pointer");
    static_assert(not is_callable_with<Foo, int, int>::value, "Does not work with single argument");
    static_assert(not is_callable_with<Foo, int, A, int>::value, "Does not work with wrong type");
    static_assert(not is_callable_with<Foo, int, A, A>::value, "Does not work with wrong type");
    static_assert(not is_callable_with<Foo, A, int, int>::value, "wrong return type");
    static_assert(not is_callable_with<Foo, int, int, int, int>::value, "too many arguments");

    static_assert(not is_callable_with<A, int, int>::value, "A not callable");

    struct NoArgs
    {
        int operator()(){return 1;}
    };
    static_assert(is_callable_with<NoArgs, int>::value, "callable with no args");
    static_assert(not is_callable_with<NoArgs, int, int>::value, "not callable with arg");

    struct VoidRet
    {
        void operator()(){};
    };
    static_assert(is_callable_with<VoidRet, void>::value, "returns void");
    static_assert(not is_callable_with<VoidRet, int>::value, "doesn't return int");
    static_assert(not is_callable_with<VoidRet, void, int>::value, "Not callable with parameter");

    struct DefaultParam
    {
        int operator()(int v = 5){return 3 + v;}
    };
    static_assert(is_callable_with<DefaultParam, int>::value, "callable with no arg");
    static_assert(is_callable_with<DefaultParam, int, int>::value, "callable with arg");

}
