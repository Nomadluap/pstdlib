

#pragma once
#include <stddef.h>
#include <stdint.h>
#include "iterator.hpp"

namespace pstd
{
    template<class T, size_t N>
    struct array
    {
        using reference = T&;
        using const_reference = T const&;
        using iterator = T*;
        using const_iterator = T const*;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using const_pointer = T const*;
        using reverse_iterator = pstd::reverse_iterator<iterator>;
        using const_reverse_iterator = pstd::reverse_iterator<const_iterator>;

        void fill(const T& u)
        {
            for(size_t i = 0; i < N; i++) _data[i] = u;
        }
        void swap(array<T, N>& other)
        {
            for(size_t i = 0; i < N; i++)
            {
                T temp     = move(other[i]);
                other[i]   = move((*this)[i]);
                (*this)[i] = move(temp);
            }
        };

        //iterators
        constexpr iterator        begin() noexcept {return _data;}
        constexpr const_iterator  begin() const noexcept {return _data;}
        constexpr iterator        end() noexcept {return _data + N;}
        constexpr const_iterator  end() const noexcept {return _data + N;}

        constexpr reverse_iterator        rbegin() noexcept {return reverse_iterator(_data + N);}
        constexpr const_reverse_iterator  rbegin() const noexcept {return const_reverse_iterator(_data + N);}
        constexpr reverse_iterator        rend() noexcept {return reverse_iterator(_data);}
        constexpr const_reverse_iterator  rend() const noexcept {return const_reverse_iterator(_data);}

        constexpr const_iterator  cbegin() const noexcept {return begin();}
        constexpr const_iterator  cend() const noexcept {return end();}
        constexpr const_iterator  crbegin() const noexcept {return rbegin();}
        constexpr const_iterator  crend() const noexcept {return rend();}

        //size
        constexpr size_type size() const noexcept {return N;}
        constexpr size_type max_size() const noexcept {return N;}
        constexpr bool      empty() const noexcept {return false;}

        //element access
        constexpr reference       operator[](size_type n) {return _data[n];}
        constexpr const_reference operator[](size_type n) const {return _data[n];}
        constexpr reference       at(size_type n) {return _data[n];}
        constexpr const_reference at(size_type n) const {return _data[n];}
        constexpr reference       front() {return _data[0];}
        constexpr const_reference front() const {return _data[0];}
        constexpr reference       back() {return _data[N-1];}
        constexpr const_reference back() const {return _data[N-1];}

        constexpr T*       data() noexcept {return _data;}
        constexpr T const* data() const noexcept {return _data;}

    private:
        T _data[N];
    };

    template<size_t I, typename T, size_t N>
    T& get(array<T, N>& arr)
    {
        static_assert(I < N, "Index must be less than size of array");
        return *(arr.data() + I);
    };
    template<size_t I, typename T, size_t N>
    T const& get(array<T, N> const& arr)
    {
        static_assert(I < N, "Index must be less than size of array");
        return *(arr.data() + I);
    };



    //swap specialization.
}




