

#include "type_traits.hpp"

using namespace pstd;
namespace
{
    class Abstract
    {
        virtual ~Abstract(){};
        virtual void dothing() = 0;
    };
    class NotAbstract
    {
        void dothing(){};
    };
    static_assert(is_abstract<Abstract>::value, "abstract");
    static_assert(not is_abstract<NotAbstract>::value, "abstract");

    static_assert(is_same<Abstract, Abstract>::value, "same");
    static_assert(not is_same<Abstract, NotAbstract>::value, "same");
    static_assert(not is_same<Abstract, Abstract const>::value, "same");
    static_assert(not is_same<Abstract, Abstract volatile>::value, "same");
    static_assert(not is_same<Abstract, Abstract const volatile>::value, "same");
    static_assert(is_same<int, int>::value, "same");
    static_assert(not is_same<int, long int>::value, "same");
    static_assert(not is_same<int, short int>::value, "same");
    static_assert(is_same<int8_t, signed char>::value, "same");
    static_assert(is_same<uint8_t, unsigned char>::value, "same");


    static_assert(is_class<Abstract>::value, "is_class");
    static_assert(not is_class<int>::value, "is_class");

    static_assert(is_same<remove_const_t<const int>, int>::value, "remove_const");
    static_assert(is_same<remove_const_t<const Abstract>, Abstract>::value, "remove_const");

    static_assert(is_same<remove_volatile_t<const int>, const int>::value, "remove_volatile");


    static_assert(is_same<remove_cv_t<int>, int>::value, "remove_cv");
    static_assert(is_same<remove_cv_t<const int>, int>::value, "remove_cv");
    static_assert(is_same<remove_cv_t<volatile int>, int>::value, "remove_cv");
    static_assert(is_same<remove_cv_t<const volatile int>, int>::value, "remove_cv");

    static_assert(not is_const<int>::value, "is const");
    static_assert(not is_const<int*>::value, "is const");
    static_assert(is_const<int const>::value, "is const");
    static_assert(not is_const<int const*>::value, "is const");
    static_assert(is_const<int* const>::value, "is const");
    static_assert(is_const<int const* const>::value, "is const");

    static_assert(is_same<add_const_t<int>, int const>::value, "add const");
    static_assert(is_same<add_const_t<int const>, int const>::value, "add const");
    static_assert(is_same<add_const_t<int*>, int* const>::value, "add const");
    static_assert(is_same<add_const_t<int const*>, int const* const>::value, "add const");

    static_assert(not is_volatile<int>::value, "is volatile");
    static_assert(is_volatile<int volatile>::value, "is volatile");

    struct A{};

    static_assert(is_same<remove_reference_t<A>, A>::value, "remove reference");
    static_assert(is_same<remove_reference_t<A& >, A>::value, "remove reference");
    static_assert(is_same<remove_reference_t<A&& >, A>::value, "remove reference");
    static_assert(is_same<remove_reference_t<A const&>, A const>::value, "remove reference");

    static_assert(not is_reference<A>::value, "is reference");
    static_assert(is_reference<A& >::value, "is reference");
    static_assert(is_reference<A const&>::value, "is reference");
    static_assert(is_reference<A &&>::value, "is reference");
    static_assert(is_reference<A const&&>::value, "is reference");

    static_assert(is_same<remove_cvref_t<A>, A>::value, "remove_cvref");
    static_assert(is_same<remove_cvref_t<A&>, A>::value, "remove_cvref");
    static_assert(is_same<remove_cvref_t<A&& >, A>::value, "remove_cvref");
    static_assert(is_same<remove_cvref_t<A const&>, A>::value, "remove_cvref");
    static_assert(is_same<remove_cvref_t<A const&&>, A>::value, "remove_cvref");
    static_assert(is_same<remove_cvref_t<A volatile&>, A>::value, "remove_cvref");
    static_assert(is_same<remove_cvref_t<A const volatile>, A>::value, "remove_cvref");

    static_assert(is_same<remove_pointer_t<int>, int>::value, "remove pointer");
    static_assert(is_same<remove_pointer_t<int const>, int const>::value, "remove pointer");
    static_assert(is_same<remove_pointer_t<int*>, int>::value, "remove pointer");
    static_assert(is_same<remove_pointer_t<int const*>, int const>::value, "remove pointer");
    static_assert(is_same<remove_pointer_t<int const* const>, int const>::value, "remove pointer");

    static_assert(rank<int>::value == 0);
    static_assert(rank<int[]>::value == 1);
    static_assert(rank<int[1]>::value == 1);
    static_assert(rank<int[20]>::value == 1);
    static_assert(rank<int[20][3]>::value == 2);

    static_assert(extent<int>::value == 0);
    static_assert(extent<int[]>::value == 0);
    static_assert(extent<int[1]>::value == 1);
    static_assert(extent<int[5]>::value == 5);
    static_assert(extent<int[5][7], 1>::value == 7);
    static_assert(extent<int[5][7], 2>::value == 0);

    static_assert(is_same<remove_extent_t<int>, int>::value);
    static_assert(is_same<remove_extent_t<int[]>, int>::value);
    static_assert(is_same<remove_extent_t<int[44]>, int>::value);
    static_assert(is_same<remove_extent_t<int[3][4]>, int[4]>::value);

    static_assert(is_same<remove_all_extents_t<int>, int>::value);
    static_assert(is_same<remove_all_extents_t<int[]>, int>::value);
    static_assert(is_same<remove_all_extents_t<int[3]>, int>::value);
    static_assert(is_same<remove_all_extents_t<int[][1]>, int>::value);
    static_assert(is_same<remove_all_extents_t<int[3][5]>, int>::value);

    static_assert(alignment_of<int>::value == alignof(int));
    static_assert(alignment_of<int[]>::value == alignof(int));
    static_assert(alignment_of<int&>::value == alignof(int));
    static_assert(alignment_of<int[5]>::value == alignof(int));

    static_assert(is_void<void>::value);
    static_assert(is_void<void const>::value);
    static_assert(is_void<void volatile>::value);
    static_assert(not is_void<int>::value);
    static_assert(not is_void<int const >::value);
    static_assert(not is_void<int**>::value);

    static_assert(is_nullptr<decltype(nullptr)>::value);
    static_assert(is_nullptr<decltype(nullptr) const>::value);
    static_assert(is_nullptr<decltype(nullptr) volatile>::value);
    static_assert(not is_nullptr<decltype(0)>::value);
    static_assert(not is_nullptr<int>::value);

    static_assert(is_integral<int>::value);
    static_assert(is_integral<short int>::value);
    static_assert(is_integral<long int>::value);
    static_assert(is_integral<unsigned>::value);
    static_assert(is_integral<unsigned int>::value);
    static_assert(is_integral<char>::value);
    static_assert(is_integral<signed char>::value);
    static_assert(is_integral<unsigned char>::value);
    static_assert(is_integral<bool>::value);
    static_assert(is_integral<long long int>::value);
    static_assert(is_integral<long long unsigned int>::value);
    static_assert(is_integral<long>::value);
    static_assert(is_integral<long long>::value);
    static_assert(is_integral<const int>::value);
    static_assert(is_integral<const char>::value);
    static_assert(is_integral<volatile int>::value);
    static_assert(is_integral<volatile const int>::value);
    static_assert(is_integral<volatile const long long int>::value);
    static_assert(not is_integral<A>::value);
    static_assert(not is_integral<float>::value);
    static_assert(not is_integral<double>::value);
    static_assert(not is_integral<long double>::value);

    static_assert(is_floating_point<float>::value);
    static_assert(is_floating_point<double>::value);
    static_assert(is_floating_point<long double>::value);
    static_assert(is_floating_point<const float>::value);
    static_assert(is_floating_point<const double>::value);
    static_assert(is_floating_point<const long double>::value);
    static_assert(is_floating_point<volatile float>::value);
    static_assert(is_floating_point<volatile double>::value);
    static_assert(is_floating_point<volatile long double>::value);
    static_assert(not is_floating_point<int>::value);
    static_assert(not is_floating_point<char>::value);
    static_assert(not is_floating_point<A>::value);
    static_assert(not is_floating_point<Abstract>::value);
    static_assert(not is_floating_point<const int>::value);
    static_assert(not is_floating_point<volatile int>::value);

    static_assert(is_signed<char>::value);
    static_assert(is_signed<int>::value);
    static_assert(is_signed<short>::value);
    static_assert(is_signed<signed char>::value);
    static_assert(is_signed<long>::value);
    static_assert(is_signed<long long>::value);

    static_assert(not is_signed<unsigned int>::value);
    static_assert(not is_signed<unsigned short>::value);
    static_assert(not is_signed<unsigned char>::value);
    static_assert(not is_signed<unsigned long>::value);
    static_assert(not is_signed<unsigned long long>::value);

    static_assert(not is_unsigned<char>::value);
    static_assert(not is_unsigned<int>::value);
    static_assert(not is_unsigned<short>::value);
    static_assert(not is_unsigned<signed char>::value);
    static_assert(not is_unsigned<long>::value);
    static_assert(not is_unsigned<long long>::value);

    static_assert(is_unsigned<unsigned int>::value);
    static_assert(is_unsigned<unsigned short>::value);
    static_assert(is_unsigned<unsigned char>::value);
    static_assert(is_unsigned<unsigned long>::value);
    static_assert(is_unsigned<unsigned long long>::value);

    static_assert(not is_array<A>::value);
    static_assert(not is_array<A const>::value);
    static_assert(is_array<A[]>::value);
    static_assert(is_array<A[][3]>::value);
    static_assert(is_array<A[4][3]>::value);

    static_assert(is_same<decay_t<A>, A>::value);
    static_assert(is_same<decay_t<A const>, A>::value);
    static_assert(is_same<decay_t<A&>, A>::value);
    static_assert(is_same<decay_t<A const&>, A>::value);
    static_assert(is_same<decay_t<A[]>, A*>::value);
    static_assert(is_same<decay_t<A const[]>, A const*>::value);
    static_assert(is_same<decay_t<A[3]>, A*>::value);
    static_assert(is_same<decay_t<void(int, int)>, void(*)(int, int)>::value);


    struct X{};
    struct Y: public X{};
    struct S{};
    struct T{operator S() {return S();}};

    struct E{ template<class T> E(T&&){}}; //takes anything in constructor.

    static_assert(is_convertible<Y*, X*>::value);
    static_assert(not is_convertible<X*, Y*>::value);
    static_assert(not is_convertible<Y*, S*>::value);
    static_assert(is_convertible<T, S>::value);
    static_assert(is_convertible<T, const T>::value);
    static_assert(is_convertible<const T, T>::value);

    static_assert(is_convertible<X, E>::value);
    static_assert(is_convertible<X*, E>::value);
    static_assert(is_convertible<X const*, E>::value);
    static_assert(is_convertible<X&&, E>::value);



}



