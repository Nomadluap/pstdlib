

#pragma once

namespace pstd {

    //checking for equivalence
    /*
    template<bool A, bool B>
    struct equivalent
    {
        constexpr static bool value = false;
    };
    template<bool A>
    struct equivalent<A, A>
    {
        constexpr static bool value = true;
    };
    */


    //universal quantifier.
    template<bool...> struct conjunction;

    template<bool First, bool... Rest>
    struct conjunction<First, Rest...>
    {
        constexpr static bool value = First and conjunction<Rest...>::value;
    };
    template<bool Only>
    struct conjunction<Only>
    {
        constexpr static bool value = Only;
    };

    //existential qualifier
    template<bool...> struct disjunction;

    template<bool First, bool... Rest>
    struct disjunction<First, Rest...>
    {
        constexpr static bool value = First or disjunction<Rest...>::value;
    };

    template<bool Only>
    struct disjunction<Only>
    {
        constexpr static bool value = Only;
    };

    template<typename T>
    struct always_false
    {
        constexpr static bool value = false;
    };

    template<typename T>
    struct always_true
    {
        constexpr static bool value = true;
    };

    template<class...>
    using void_t = void;
}




