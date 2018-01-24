#pragma once
#include "template_ops.hpp"
#include <stdint.h>
#include <stddef.h>

namespace pstd{

    template<typename T, T Val>
    struct integral_constant
    {
        using type = integral_constant<T, Val>;
        using value_type = T;
        constexpr static T value = Val;

        constexpr operator value_type() const noexcept
        {
            return Val;
        }
        constexpr value_type operator()() const noexcept
        {
            return Val;
        }
    };

    template<bool B>
    using boolean_constant = integral_constant<bool, B>;

    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;

    //some have compiler builtins.
    // https://gcc.gnu.org/onlinedocs//gcc/Type-Traits.html
    template<typename T>
    struct is_nothrow_assignable: public boolean_constant<__has_nothrow_assign(T)>{};

    template<typename T>
    struct is_nothrow_copyable: public boolean_constant< __has_nothrow_copy(T)>{};

    template<typename T>
    struct is_nothrow_constructable: public boolean_constant<__has_nothrow_constructor(T)>{};

    template<typename T>
    struct is_trivially_assignable: public boolean_constant<__has_trivial_assign(T)>{};

    template<typename T>
    struct is_trivially_copyable: public boolean_constant<__has_trivial_copy(T)>{};

    template<typename T>
    struct is_trivially_constructible: public boolean_constant<__has_trivial_constructor(T)>{};

    template<typename T>
    struct is_trivially_destructable: public boolean_constant<__has_trivial_destructor(T)>{};

    template<typename T>
    struct has_virtual_destructor: public boolean_constant<__has_virtual_destructor(T)>{};

    template<typename T>
    struct is_abstract: public boolean_constant<__is_abstract(T)>{};

    template<typename BaseType, typename DerivedType>
    struct is_base_of: public boolean_constant<__is_base_of(BaseType, DerivedType)>{};

    template<typename T>
    struct is_class: public boolean_constant<__is_class(T)>{};

    template<typename T>
    struct is_empty: public boolean_constant<__is_empty(T)>{};

    template<typename T>
    struct is_enum: public boolean_constant<__is_enum(T)>{};

    template<typename T>
    struct is_literal_type: public boolean_constant<__is_literal_type(T)>{};

    template<typename T>
    struct is_pod: public boolean_constant<__is_pod(T)>{};

    template<typename T>
    struct is_polymorphic: public boolean_constant<__is_polymorphic(T)>{};

    template<typename T>
    struct is_standard_layout: public boolean_constant<__is_standard_layout(T)>{};

    template<typename T>
    struct is_trivial: public boolean_constant<__is_trivial(T)>{};

    template<typename T>
    struct is_union: public boolean_constant<__is_union(T)>{};

    template<typename T>
    struct underlying_type
    {
        using type = __underlying_type(T);
    };

    //remove const, volatile
    template<typename T> struct remove_const {using type = T;};
    template<typename T> struct remove_const<const T> {using type = T;};

    template<typename T> struct remove_volatile {using type = T;};
    template<typename T> struct remove_volatile<volatile T> {using type = T;};

    template<typename T>
    struct remove_cv
    {
        using type = typename remove_const<typename remove_volatile<T>::type>::type;
    };
    //helpers.
    template<typename T>
    using remove_const_t = typename remove_const<T>::type;
    template<typename T>
    using remove_volatile_t = typename remove_volatile<T>::type;
    template<typename T>
    using remove_cv_t = typename remove_cv<T>::type;

    template<typename T>
    struct is_const: public false_type{};
    template<typename T>
    struct is_const<const T>: public true_type{};

    template<typename T> struct add_const {using type = T const;};
    template<typename T> struct add_volatile {using type = T volatile;};
    template<typename T> using add_const_t = typename add_const<T>::type;
    template<typename T> using add_volatile_t = typename add_volatile<T>::type;


    template<typename T>
    struct is_volatile: public false_type{};
    template<typename T>
    struct is_volatile<volatile T>: public true_type{};

    //remove reverence
    template<typename T> struct remove_reference {using type = T;};
    template<typename T> struct remove_reference<T&> {using type = T;};
    template<typename T> struct remove_reference<T&&> {using type = T;};

    template<typename T> struct is_reference: public false_type{};
    template<typename T> struct is_reference<T&>: public true_type{};
    template<typename T> struct is_reference<T&&>: public true_type{};

    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    template<typename T>
    struct remove_cvref
    {
        using type = typename remove_cv<typename remove_reference<typename remove_cv<T>::type>::type>::type;
    };
    template<typename T>
    using remove_cvref_t = typename remove_cvref<T>::type;

    template<typename T> struct remove_pointer {using type = T;};
    template<typename T> struct remove_pointer<T*> {using type = T;};
    template<typename T> struct remove_pointer<T* const> {using type = T;};
    template<typename T> struct remove_pointer<T* volatile> {using type = T;};
    template<typename T>
    using remove_pointer_t = typename remove_pointer<T>::type;




    // Rank: size of a c-array.
    template<typename T>
    struct rank: public integral_constant<size_t, 0>{};
    template<typename T>
    struct rank<T[]>: public integral_constant<size_t, rank<T>::value + 1>{};
    template<typename T, size_t N>
    struct rank<T[N]>: public integral_constant<size_t, rank<T>::value + 1>{};

    //Extent: size of a given dimension of a c-array.
    template<typename T, unsigned N = 0>
    struct extent: integral_constant<size_t, 0>{};
    template<typename T>
    struct extent<T[], 0>: integral_constant<size_t, 0>{};
    template<typename T, unsigned N>
    struct extent<T[], N>: extent<T, N-1>{};
    template<typename T, size_t I>
    struct extent<T[I], 0>: integral_constant<size_t, I>{};
    template<typename T, size_t I, unsigned N>
    struct extent<T[I], N>: extent<T, N-1>{};

    //remove extent
    template<typename T> struct remove_extent {using type = T;};
    template<typename T> struct remove_extent<T[]> {using type = T;};
    template<typename T, size_t N> struct remove_extent<T[N]> {using type = T;};
    template<typename T> using remove_extent_t = typename remove_extent<T>::type;

    template<typename T>
    struct remove_all_extents{using type = T;};
    template<typename T>
    struct remove_all_extents<T[]>{using type = typename remove_all_extents<T>::type;};
    template<typename T, size_t N>
    struct remove_all_extents<T[N]>{using type = typename remove_all_extents<T>::type;};
    template<typename T>
    using remove_all_extents_t = typename remove_all_extents<T>::type;

    //alignment
    template<typename T> struct alignment_of
    {
        constexpr static size_t value = alignof(typename remove_extent<typename remove_reference<T>::type>::type);
    };

    /*
     * Is same is true iff the type of A is the type of b, and they are both equally cv-qualified.
     */
    template<typename S, typename T> struct is_same: false_type{};
    template<typename T> struct is_same<T, T>: true_type{};

    template<typename T> struct is_void: is_same<remove_cv_t<T>, void>{};
    template<typename T> struct is_nullptr: is_same<remove_cv_t<T>, nullptr_t>{};

    //is integral
    namespace detail
    {
        template<typename T> struct is_integral: false_type{};
        template<> struct is_integral<char>: true_type{};
        template<> struct is_integral<char16_t>: true_type{};
        template<> struct is_integral<char32_t>: true_type{};
        template<> struct is_integral<short>: true_type{};
        template<> struct is_integral<int>: true_type{};
        template<> struct is_integral<long>: true_type{};
        template<> struct is_integral<long long>: true_type{};
        template<> struct is_integral<unsigned char>: true_type{};
        template<> struct is_integral<signed char>: true_type{};
        template<> struct is_integral<unsigned short>: true_type{};
        template<> struct is_integral<unsigned int>: true_type{};
        template<> struct is_integral<unsigned long>: true_type{};
        template<> struct is_integral<unsigned long long>: true_type{};
        template<> struct is_integral<bool>: true_type{};
    }
    template<typename T> struct is_integral: detail::is_integral<remove_cv_t<T>>{};

    //is floating point
    namespace detail
    {
        template<typename T> struct is_floating_point: false_type{};
        template<> struct is_floating_point<float>: true_type{};
        template<> struct is_floating_point<double>: true_type{};
        template<> struct is_floating_point<long double>: true_type{};
    }
    template<typename T> struct is_floating_point: detail::is_floating_point<remove_cv_t<T>>{};

    //is arithmetic
    template<typename T> struct is_arithmetic: disjunction<
    is_integral<T>::value,
    is_floating_point<T>::value
    >{};

    namespace detail {
        template<typename T, bool = is_arithmetic<T>::value>
        struct is_unsigned: boolean_constant<(T(0) < T(-1))>{};
        template<typename T>
        struct is_unsigned<T, false>: false_type{};

        template<typename T, bool = is_arithmetic<T>::value>
        struct is_signed: boolean_constant<T(-1) < T(0)>{};
        template<typename T>
        struct is_signed<T, false>: false_type{};
    }
    template<typename T>
    struct is_unsigned: detail::is_unsigned<T>::type{};
    template<typename T>
    struct is_signed: detail::is_signed<T>::type{};

    template<typename T> struct is_array: false_type{};
    template<typename T> struct is_array<T[]>: true_type{};
    template<typename T, size_t N> struct is_array<T[N]>: true_type{};

    template<typename T> struct is_lvalue_reference: false_type{};
    template<typename T> struct is_lvalue_reference<T&>: true_type{};

    template<typename T> struct is_rvalue_reference: false_type{};
    template<typename T> struct is_rvalue_reference<T&&>: true_type{};

    template<typename T> struct is_function: false_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)>: true_type{};
    //cv-qualified
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)const >: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)volatile>: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)const volatile>: true_type{};
    //with references.
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)& >: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)const & >: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)volatile &>: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)const volatile &>: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)&& >: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)const && >: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)volatile &&>: true_type{};
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)const volatile &&>: true_type{};


    namespace detail{
        template<typename T, bool is_function_type = false>
        struct add_pointer{
            using type = typename remove_reference<T>::type*;
        };
        template<typename T>
        struct add_pointer<T, true>
        {
            using type = T;
        };
        template<typename T, typename... Args>
        struct add_pointer<T(Args...), true>
        {
            using type = T(*)(Args...);
        };
    }
    template<typename T>
    struct add_pointer: detail::add_pointer<T, is_function<T>::value>{};


    template<typename T> struct is_fundamental: disjunction<
        is_arithmetic<T>::value,
        is_void<T>::value,
        is_nullptr<T>::value
    >{};

    template<typename T> struct is_compound: boolean_constant<not is_fundamental<T>::value>{};

    template<bool B, typename T = void> struct enable_if{};
    template<class T> struct enable_if<true, T> {using type = T;};
    template<bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    template<bool B, typename T, typename F> struct conditional{ using type = T;};
    template<typename T, typename F> struct conditional<false, T, F> {using type = F;};

    template<typename T>
    struct decay
    {
    private:
        using U = typename remove_reference<T>::type;
    public:
        using type = typename conditional<
            is_array<U>::value,
            typename remove_extent<U>::type*,
            typename conditional<
                is_function<U>::value,
                typename add_pointer<U>::type,
                typename remove_cv<U>::type
            >::type
        >::type;
    };

    template<typename T> using decay_t = typename decay<T>::type;

    template<size_t Len, size_t Align>
    struct aligned_storage
    {
        struct type
        {
            alignas(Align) unsigned char data[Len];
        };
    };

    //intentionally no definition.
    template<typename T>
    T&& declval() noexcept;

    namespace detail
    {
        template<class From, class To, bool = is_void<From>::value or is_function<To>::value or is_array<To>::value>
        struct is_convertible_helper {using type = typename is_void<To>::type;};

        template<class From, class To>
        class is_convertible_helper<From, To, false>
        {
            template<typename To1>
            static void test_aux(To1);

            template<typename From1, typename To1,
                typename = decltype(test_aux<To1>(declval<From1>()))>
            static true_type test(int);

            template<typename, typename> static false_type test(...);

        public:
            using type = typename decltype(test<From, To>(0))::type;

        };
    }
    template<class From, class To>
    struct is_convertible: public detail::is_convertible_helper<From, To>::type{};

}
