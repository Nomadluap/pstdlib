

#pragma once
#ifndef _INITIALIZER_LIST
#define _INITIALIZER_LIST //to prevent import of g++ <initializer_list> when testing.
#include <stddef.h>

namespace std {
    template<class E>
    class initializer_list
    {
    public:
        using value_type = E;
        using reference = const E&;
        using const_reference = const E&;
        using size_type = size_t;
        using iterator = E const*;
        using const_iterator = E const*;

        constexpr initializer_list() noexcept: _array(nullptr), _size(0){};

        constexpr size_t size() const noexcept {return _size;}
        constexpr const_iterator begin() const noexcept {return _array;}
        constexpr const_iterator end() const noexcept{return _array + _size;}

    private:
        iterator _array;
        size_type _size;

        constexpr initializer_list(iterator arr, size_type size): _array(arr), _size(size){};
    };

}

namespace pstd {
    using std::initializer_list;
}



#endif //_INITIALIZER_LIST



