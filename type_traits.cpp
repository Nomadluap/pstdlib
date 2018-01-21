

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




}



