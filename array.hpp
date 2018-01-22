

#pragma once
#include <stddef.h>
#include <stdint.h>
#include "initializer_list.hpp"
#include "iterator.hpp"
#include "utility.hpp"

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
            for(size_t i = 0; i < N; i++) _M_data[i] = u;
        }
        void swap(array<T, N>& other)
        {
            for(size_t i = 0; i < N; i++)
            {
                swap((*this)[i], other[i]);
            }
        };

        //iterators
        constexpr iterator        begin() noexcept {return _M_data;}
        constexpr const_iterator  begin() const noexcept {return _M_data;}
        constexpr iterator        end() noexcept {return _M_data + N;}
        constexpr const_iterator  end() const noexcept {return _M_data + N;}

        constexpr reverse_iterator        rbegin() noexcept {return reverse_iterator(_M_data + N);}
        constexpr const_reverse_iterator  rbegin() const noexcept {return const_reverse_iterator(_M_data + N);}
        constexpr reverse_iterator        rend() noexcept {return reverse_iterator(_M_data);}
        constexpr const_reverse_iterator  rend() const noexcept {return const_reverse_iterator(_M_data);}

        constexpr const_iterator  cbegin() const noexcept {return begin();}
        constexpr const_iterator  cend() const noexcept {return end();}
        constexpr const_iterator  crbegin() const noexcept {return rbegin();}
        constexpr const_iterator  crend() const noexcept {return rend();}

        //size
        constexpr size_type size() const noexcept {return N;}
        constexpr size_type max_size() const noexcept {return N;}
        constexpr bool      empty() const noexcept {return false;}

        //element access
        constexpr reference       operator[](size_type n) {return _M_data[n];}
        constexpr const_reference operator[](size_type n) const {return _M_data[n];}
        constexpr reference       at(size_type n)
        {
            //todo: throw exception here.
            return _M_data[n];
        }
        constexpr const_reference at(size_type n) const
        {
            //todo: Throw exception here.
            return _M_data[n];
        }
        constexpr reference       front() {return _M_data[0];}
        constexpr const_reference front() const {return _M_data[0];}
        constexpr reference       back() {return _M_data[N-1];}
        constexpr const_reference back() const {return _M_data[N-1];}

        constexpr T*       data() noexcept {return _M_data;}
        constexpr T const* data() const noexcept {return _M_data;}


        T _M_data[N]; //must be publilc for aggregeate initialization.
    };

    //specialization of get.
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
    //relational operators.
    template<class T, size_t N>
    constexpr bool operator==(array<T, N> const& lhs, array<T, N> const& rhs)
    {
        for(size_t i = 0; i < N; i++)
        {
            if(lhs[i] == rhs[i]) continue;
            else
            {
                return false;
            }
        }
        return true;
    };
    template<class T, size_t N>
    constexpr bool operator!=(array<T, N> const& lhs, array<T, N> const& rhs)
    {
        for(size_t i = 0; i < N; i++)
        {
            if(lhs[i] != rhs[i]) continue;
            else
            {
                return false;
            }
        }
        return true;
    };
    template<class T, size_t N>
    constexpr bool operator<(array<T, N> const& lhs, array<T, N> const& rhs)
    {
        for(size_t i = 0; i < N; i++)
        {
            if(lhs[i] < rhs[i]) return true;
            else if (rhs[i] < lhs[i]) return false;
        }
        return false;
    };
    template<class T, size_t N>
    constexpr bool operator<=(array<T, N> const& lhs, array<T, N> const& rhs)
    {
        for(size_t i = 0; i < N; i++)
        {
            if(lhs[i] < rhs[i]) return true;
            else if (rhs[i] < lhs[i]) return false;
        }
        return true;
    };
    template<class T, size_t N>
    constexpr bool operator>(array<T, N> const& lhs, array<T, N> const& rhs)
    {
        for(size_t i = 0; i < N; i++)
        {
            if(lhs[i] > rhs[i]) return true;
            else if (rhs[i] > lhs[i]) return false;
        }
        return false;
    };
    template<class T, size_t N>
    constexpr bool operator>=(array<T, N> const& lhs, array<T, N> const& rhs)
    {
        for(size_t i = 0; i < N; i++)
        {
            if(lhs[i] > rhs[i]) return true;
            else if (rhs[i] > lhs[i]) return false;
        }
        return true;
    };

    template<class T, size_t N>
    void swap(array<T, N>& lhs, array<T, N>& rhs)
    {
        lhs.swap(rhs);
    };

    template<class T, size_t N>
    struct tuple_size<array<T, N> >: integral_constant<size_t , N>{};


    template<size_t I, class T, size_t N>
    struct tuple_element<I, array<T, N> >
    {
        static_assert(I < N, "Index I must be smaller than array size");
        using type = T;
    };





}




