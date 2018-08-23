

#include "extra_type_traits.hpp"

using namespace PSTDLIB_NAMESPACE;

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


    static_assert(is_invocable_r<Foo, int, int, int>::value, "Foo callable with ints");
    static_assert(is_invocable_r<Foo, double, int, int>::value, "Implicit return type conversion");
    static_assert(is_invocable_r<Foo, IntCtor, int, int>::value, "IMplicit return type conversion");
    static_assert(is_invocable_r<Foo, int, char, char>::value, "Implicit argument conversion");
    static_assert(is_invocable_r<Foo, int, int, char>::value, "Implicit argument conversion");
    static_assert(is_invocable_r<Foo, int, ImplicitInt, int>::value, "implicit argument conversion");

    static_assert(not is_invocable_r<Foo, int*, int, int>::value, "Does not return pointer");
    static_assert(not is_invocable_r<Foo, int, int>::value, "Does not work with single argument");
    static_assert(not is_invocable_r<Foo, int, A, int>::value, "Does not work with wrong type");
    static_assert(not is_invocable_r<Foo, int, A, A>::value, "Does not work with wrong type");
    static_assert(not is_invocable_r<Foo, A, int, int>::value, "wrong return type");
    static_assert(not is_invocable_r<Foo, int, int, int, int>::value, "too many arguments");

    static_assert(not is_invocable_r<A, int, int>::value, "A not callable");

    struct NoArgs
    {
        int operator()(){return 1;}
    };
    static_assert(is_invocable_r<NoArgs, int>::value, "callable with no args");
    static_assert(not is_invocable_r<NoArgs, int, int>::value, "not callable with arg");

    struct VoidRet
    {
        void operator()(){};
    };
    static_assert(is_invocable_r<VoidRet, void>::value, "returns void");
    static_assert(not is_invocable_r<VoidRet, int>::value, "doesn't return int");
    static_assert(not is_invocable_r<VoidRet, void, int>::value, "Not callable with parameter");

    struct DefaultParam
    {
        int operator()(int v = 5){return 3 + v;}
    };
    static_assert(is_invocable_r<DefaultParam, int>::value, "callable with no arg");
    static_assert(is_invocable_r<DefaultParam, int, int>::value, "callable with arg");
    static_assert(not is_invocable_r<DefaultParam, VoidRet, int>::value, "Not returning double");
    static_assert(not is_invocable_r<DefaultParam, void, int>::value, "does not return void");


    auto lambda = [](int i) {return i+1;};

    static_assert(is_invocable_r<decltype(lambda), int, int>::value, "lambda callable");
    static_assert(not is_invocable_r<decltype(lambda), int>::value, "not callable with nothing");
    static_assert(not is_invocable<decltype(lambda), DefaultParam>::value, "not callable with non-arithmetic");

    auto l2 = [](auto i){return i+1;};
    static_assert(is_invocable_r<decltype(l2), double, double>::value, "callable with double");
    static_assert(is_invocable_r<decltype(l2), int, int>::value, "callable with int");
    static_assert(is_invocable_r<decltype(l2), uint8_t, uint8_t>::value, "callable with uint8_t");

}
