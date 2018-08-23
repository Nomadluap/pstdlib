

#pragma once
#include "type_traits.hpp"
#include "pstdlib_namespace.hpp"

namespace PSTDLIB_NAMESPACE
{
    template<typename T>
    constexpr inline typename remove_reference<T>::type&& move(T&& t) noexcept
    {
        return static_cast<typename remove_reference<T>::type&&>(t);
    }

    /*
    template<class T>
    constexpr inline T&& forward(typename remove_reference<T>::type& t) noexcept
    {
        return static_cast<T&&>(t);
    }
    template<class T>
    constexpr inline T&& forward(typename remove_reference<T>::type&& t) noexcept
    {
        static_assert(not is_lvalue_reference<T>::value, "Can not forward rvalue as lvalue");
        return static_cast<T&&>(t);
    }
    */

    //see http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2009/n2951.html
    template <class T, class U,
    class = typename enable_if<
         (is_lvalue_reference<T>::value ?
             is_lvalue_reference<U>::value :
             true) &&
         is_convertible<typename remove_reference<U>::type*,
                        typename remove_reference<T>::type*>::value
        >::type>
    inline
    T&&
    forward(U&& u)
    {
        return static_cast<T&&>(u);
    }


    //specialize this for your own custom types if swapping can be more efficient!
    template<typename T>
    void swap(T& a, T& b)
    {
        T temp = move(a);
        a = move(b);
        b = move(temp);
    }

    template<typename T, typename U = T>
    constexpr T exchange(T& obj, U&& new_value)
    {
        T old_value = obj;
        obj = forward<U>(new_value);
        return old_value;
    };

    template<typename T>
    constexpr add_const<T>& as_const(T& t) noexcept
    {
        return t;
    }
    template<class T>
    void as_const(const T&&) = delete;


    template<class T1, class T2>
    struct pair
    {
        using first_type = T1;
        using second_type = T2;

        first_type first;
        second_type second;

        constexpr pair(): first(), second(){}
        constexpr pair(T1 const& x, T2 const& y): first(x), second(y){}

        template<class U1, class U2>
        constexpr pair(U1&& x, U2&&y): first(x), second(y){};

        template<class U1, class U2>
        constexpr pair(pair<U1, U2> const& p): first(p.first), second(p.second){};

        template<class U1, class U2>
        constexpr pair(pair<U1, U2>&& p): first(move(p.first)), second(move(p.second)){};

        constexpr pair(pair<T1, T2> const& p) = default;
        constexpr pair(pair<T1, T2> && p) = default;

        pair<T1, T2>& operator=(pair<T1, T2> const& other) = default;
        pair<T1, T2>& operator=(pair<T1, T2>&& other) = default;

        template<class U1, class U2>
        pair<T1, T2>& operator=(pair<U1, U2> const& other)
        {
            this->first = other.first;
            this->second = other.second;
            return *this;
        };
        template<class U1, class U2>
        pair<T1, T2>& operator=(pair<U1, U2> && other)
        {
            this->first = move(other.first);
            this->second = move(other.second);
            return *this;
        };

        void swap(pair<T1, T2>& other)
        {
            pstd::swap(this->first, other.first);
            pstd::swap(this->second, other.second);
        }
    };
    template<typename T1, typename T2>
    pair<T1, T2> make_pair(T1&& t1, T2&& t2){ return pair<T1, T2>(forward<T1>(t1), forward<T2>(t2));};

    template<class T1, class T2>
    bool operator==(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs){return lhs.first == rhs.first and lhs.second == rhs.second;};

    template<class T1, class T2>
    bool operator!=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs){return lhs.first != rhs.first or lhs.second != rhs.second;};

    template<class T1, class T2>
    bool operator<(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
    {
        if(lhs.first < rhs.first) return true;
        else if(lhs.first == rhs.first and lhs.second < rhs.second) return true;
        return false;
    };

    template<class T1, class T2>
    bool operator<=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
    {
        if(lhs.first <= rhs.first) return true;
        else if(lhs.first == rhs.first and lhs.second <= rhs.second) return true;
        return false;
    };

    template<class T1, class T2>
    bool operator>(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
    {
        if(lhs.first > rhs.first) return true;
        else if(lhs.first == rhs.first and lhs.second > rhs.second) return true;
        return false;
    };

    template<class T1, class T2>
    bool operator>=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
    {
        if(lhs.first >= rhs.first) return true;
        else if(lhs.first == rhs.first and lhs.second >= rhs.second) return true;
        return false;
    };

    template<class T1, class T2>
    void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs)
    {
        lhs.swap(rhs);
    };

    template<size_t I, class Container>
    struct tuple_element;

    template<class T>
    struct tuple_size;

    template<class T>
    struct tuple_size<const T>: integral_constant<size_t, tuple_size<T>::value>{};

    template<class T>
    struct tuple_size<volatile T>: integral_constant<size_t, tuple_size<T>::value>{};

    template<class T>
    struct tuple_size<const volatile T>: integral_constant<size_t, tuple_size<T>::value>{};


    template<size_t I, class Container>
    using tuple_element_t = typename tuple_element<I, Container>::type;

    //tuple_element specialization for pair.
    template<class T1, class T2>
    struct tuple_element<0, pair<T1, T2>>
    {
        using type = T1;
    };
    template<class T1, class T2>
    struct tuple_element<1, pair<T1, T2>>
    {
        using type = T2;
    };

    template<typename T1, typename T2>
    struct tuple_size<pair<T1, T2>>: public integral_constant<size_t, 2>{};

    namespace detail
    {
        template<size_t I, class T1, class T2> struct get_pair_helper;

        template<class T1, class T2> struct get_pair_helper<0, T1, T2>
        {
            using pair_type = pair<T1, T2>;
            using value_type = T1;

            constexpr static value_type&       get(pair_type& p)       {return p.first;}
            constexpr static value_type const& get(pair_type const& p) {return p.first;}
            constexpr static value_type&&      get(pair_type&& p)      {return move(p.first);}
        };
        template<class T1, class T2> struct get_pair_helper<1, T1, T2>
        {
            using pair_type = pair<T1, T2>;
            using value_type = T2;

            constexpr static value_type&       get(pair_type& p)       {return p.second;}
            constexpr static value_type const& get(pair_type const& p) {return p.second;}
            constexpr static value_type&&      get(pair_type&& p)      {return move(p.second);}
        };
    }

    //get non-const ref.
    template<size_t I, class T1, class T2>
    constexpr tuple_element_t<I, pair<T1, T2>>& get(pair<T1, T2>& p)
    {
        return detail::get_pair_helper<I, T1, T2>::get(p);
    };
    //const ref
    template<size_t I, class T1, class T2>
    constexpr tuple_element_t<I, pair<T1, T2>> const& get(pair<T1, T2> const& p)
    {
        return detail::get_pair_helper<I, T1, T2>::get(p);
    };
    //rvalue ref
    template<size_t I, class T1, class T2>
    constexpr tuple_element_t<I, pair<T1, T2>>&& get(pair<T1, T2>&& p)
    {
        return detail::get_pair_helper<I, T1, T2>::get(move(p));
    };









}





