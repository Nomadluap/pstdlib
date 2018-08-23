#pragma once
#include <stddef.h>
#include <stdint.h>
#include "type_traits.hpp"
#include "utility.hpp"
#include "pstdlib_namespace.hpp"

namespace PSTDLIB_NAMESPACE {
    /**
     * Iterator tag types
     */
    struct input_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    struct output_iterator_tag { };

    //by default pulls from the Iterator itself.
    template<typename Iterator>
    struct iterator_traits
    {
        using difference_type   = typename Iterator::difference_type;
        using value_type        = typename Iterator::value_type;
        using pointer           = typename Iterator::pointer;
        using reference         = typename Iterator::reference;
        using iterator_category = typename Iterator::iterator_category;
    };
    /**
     * iterator_traits specialization for pointer types since they can't have nested members.
     */
    template<typename T>
    struct iterator_traits<T *>
    {
        using difference_type = ptrdiff_t;
        using value_type = remove_cv_t<T>;
        using pointer = T *;
        using reference = T &;
        using iterator_category = random_access_iterator_tag;
    };

    template<typename Iter>
    using is_input_iterator = is_base_of<input_iterator_tag, typename iterator_traits<Iter>::iterator_category >;

    template<typename Iter>
    using is_forward_iterator = is_base_of<forward_iterator_tag, typename iterator_traits<Iter>::iterator_category >;

    template<typename Iter>
    using is_bidirectional_iterator = is_base_of<bidirectional_iterator_tag, typename iterator_traits<Iter>::iterator_category >;

    template<typename Iter>
    using is_random_access_iterator = is_base_of<random_access_iterator_tag, typename iterator_traits<Iter>::iterator_category >;




    /**
     * Reverse iterator adaptor.
     * @tparam Iter
     */
    template<class Iter>
    struct reverse_iterator
    {
        static_assert(is_random_access_iterator<Iter>::value, "Iter must be a random access iterator. ");
        using difference_type   = typename iterator_traits<Iter>::difference_type;
        using value_type        = typename iterator_traits<Iter>::value_type;
        using pointer           = typename iterator_traits<Iter>::pointer;
        using reference         = typename iterator_traits<Iter>::reference;
        using iterator_category = typename iterator_traits<Iter>::iterator_category;

        reverse_iterator(): val(){}
        constexpr explicit reverse_iterator(Iter x): val(x){};
        constexpr reverse_iterator(reverse_iterator<Iter>const & other): val(other.val){};
        constexpr reverse_iterator<Iter> operator=(reverse_iterator<Iter> const& other) {val = other.val;}

        constexpr Iter base() const {return val;}

        constexpr reference operator*() const
        {
            Iter tmp = val;
            return *--tmp;
        }
        constexpr pointer operator->() const
        {
            return &(operator*());
        }

        constexpr reference operator[](difference_type n) const
        {
            return val[-n-1];
        }

        //pre-increment
        constexpr reverse_iterator<Iter>& operator++()
        {
            --val;
            return *this;
        }
        constexpr reverse_iterator<Iter>& operator--()
        {
            ++val;
            return *this;
        }
        //post-increment
        constexpr reverse_iterator<Iter>& operator++(int)
        {
            reverse_iterator<Iter> ret = *this;
            val--;
            return ret;
        }
        constexpr reverse_iterator<Iter>& operator--(int)
        {
            reverse_iterator<Iter> ret = *this;
            val++;
            return ret;
        }
        constexpr reverse_iterator<Iter> operator+(difference_type n) const
        {
            return reverse_iterator<Iter>(base() - n);
        }
        constexpr reverse_iterator<Iter> operator-(difference_type n) const
        {
            return reverse_iterator<Iter>(base() + n);
        }
        constexpr reverse_iterator<Iter>& operator+=(difference_type n)
        {
            val -= n;
            return *this;
        }
        constexpr reverse_iterator<Iter>& operator-=(difference_type n)
        {
            val += n;
            return *this;
        }
    private:
        Iter val;
    };

    template<class Iterator>
    reverse_iterator<Iterator> make_reverse_iterator(Iterator it){return reverse_iterator<Iterator>(it);}

    template<class Iterator>
    constexpr reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        reverse_iterator<Iterator> const& it
    )
    {
        return reverse_iterator<Iterator>(it.base() - n);
    }
    template<class Iterator>
    constexpr reverse_iterator<Iterator> operator-(
        typename reverse_iterator<Iterator>::difference_type n,
        reverse_iterator<Iterator> const& it
    )
    {
        return reverse_iterator<Iterator>(it.base() + n);
    }
    template<class It1, class It2>
    constexpr auto operator-(reverse_iterator<It1> const& lhs, reverse_iterator<It2> const& rhs) -> decltype(rhs.base() - lhs.base())
    {
        return rhs.base() - lhs.base();
    };

    template<class It1, class It2>
    constexpr bool operator==(reverse_iterator<It1> const& it1, reverse_iterator<It2> const& it2)
    {
        return it1.base() == it2.base();
    };
    template<class It1, class It2>
    constexpr bool operator!=(reverse_iterator<It1> const& it1, reverse_iterator<It2> const& it2)
    {
        return it1.base() != it2.base();

    };
    template<class It1, class It2>
    constexpr bool operator<(reverse_iterator<It1> const& it1, reverse_iterator<It2> const& it2)
    {
        return it1.base() > it2.base();

    };
    template<class It1, class It2>
    constexpr bool operator<=(reverse_iterator<It1> const& it1, reverse_iterator<It2> const& it2)
    {
        return it1.base() >= it2.base();

    };
    template<class It1, class It2>
    constexpr bool operator>(reverse_iterator<It1> const& it1, reverse_iterator<It2> const& it2)
    {
        return it1.base() < it2.base();

    };
    template<class It1, class It2>
    constexpr bool operator>=(reverse_iterator<It1> const& it1, reverse_iterator<It2> const& it2)
    {
        return it1.base() <= it2.base();
    };

    namespace detail
    {
        template<typename C, typename = void>
        struct has_push_back: false_type{};

        template<typename C>
        struct has_push_back<C, void_t<
            decltype(declval<C>().push_back(declval<typename C::value_type>()))
        >>: true_type{};
    }


    template<typename Container>
    struct back_insert_iterator
    {
        using difference_type = void;
        using value_type = void;
        using pointer = void;
        using reference = void;
        using iterator_category = output_iterator_tag;
        explicit back_insert_iterator(Container& c): c(c){};

        back_insert_iterator<Container>& operator=(typename Container::value_type const& obj)
        {
            c.push_back(obj);
            return *this;
        }
        back_insert_iterator<Container>& operator=(typename Container::value_type&& obj)
        {
            c.push_back(obj);
            return *this;
        }
        back_insert_iterator<Container>& operator*() { return *this; }
        back_insert_iterator<Container>& operator++() {return *this;}
        back_insert_iterator<Container>& operator++(int) {return *this;}
    private:
        Container& c;
    };

    template<typename Container>
    struct front_insert_iterator
    {
        using difference_type = void;
        using value_type = void;
        using pointer = void;
        using reference = void;
        using iterator_category = output_iterator_tag;
        explicit front_insert_iterator(Container& c): c(c){};

        front_insert_iterator<Container>& operator=(typename Container::value_type const& obj)
        {
            c.push_front(obj);
            return *this;
        }
        front_insert_iterator<Container>& operator=(typename Container::value_type&& obj)
        {
            c.push_front(obj);
            return *this;
        }
        front_insert_iterator<Container>& operator*() { return *this; }
        front_insert_iterator<Container>& operator++() {return *this;}
        front_insert_iterator<Container>& operator++(int) {return *this;}
    private:
        Container& c;
    };

    template<typename Container>
    struct insert_iterator
    {
        using difference_type = void;
        using value_type = void;
        using pointer = void;
        using reference = void;
        using iterator_category = output_iterator_tag;

        explicit insert_iterator(Container& c, typename Container::iterator i): c(c), i(i){};

        insert_iterator<Container>& operator=(typename Container::value_type const& obj)
        {
            c.insert(i, obj);
            i++;
            return *this;
        }
        insert_iterator<Container>& operator=(typename Container::value_type&& obj)
        {
            c.insert(i, move(obj));
            i++;
            return *this;
        }
        insert_iterator<Container>& operator*() { return *this; }
        insert_iterator<Container>& operator++() {return *this;}
        insert_iterator<Container>& operator++(int) {return *this;}
    private:
        Container& c;
        typename Container::iterator i;
    };

    template<typename Container>
    back_insert_iterator<Container> back_inserter(Container& c) {return back_insert_iterator<Container>(c);}
    template<typename Container>
    front_insert_iterator<Container> front_inserter(Container& c) {return front_insert_iterator<Container>(c);}
    template<typename Container>
    insert_iterator<Container> inserter(Container& c, typename Container::iterator i) {return insert_iterator<Container>(c, i);}

    namespace detail
    {
        template<class InputIt, class Distance, class iterator_tag>
        struct advance_helper
        {
            constexpr static void advance(InputIt& it, Distance n)
            {
                while(n > 0)
                {
                    ++it;
                    n--;
                }
            };
        };
        //special case: iterator is random-access.
        template<class InputIt, class Distance>
        struct advance_helper<InputIt, Distance, random_access_iterator_tag>
        {
            constexpr static void advance(InputIt& it, Distance n)
            {
                it = it + n;
            };
        };
    }
    template<class InputIt, class Distance>
    constexpr void advance(InputIt& it, Distance n)
    {
        detail::advance_helper<InputIt, Distance, typename iterator_traits<InputIt>::iterator_category>::advance(it, n);
    };

    namespace detail
    {
        template<class InputIt, class Tag>
        struct distance_helper
        {
            using difference_type = typename iterator_traits<InputIt>::difference_type;
            constexpr static difference_type distance(InputIt first, InputIt second)
            {
                typename iterator_traits<InputIt>::difference_type count = 0;
                while(not(++first == second))
                {
                    count++;
                }
                return count;
            }
        };
        //special case for random access.
        template<class InputIt>
        struct distance_helper<InputIt, random_access_iterator_tag>
        {
            using difference_type = typename iterator_traits<InputIt>::difference_type;
            constexpr static difference_type distance(InputIt first, InputIt second)
            {
                return second - first;
            }
        };
    }
    template<typename InputIt>
    constexpr typename iterator_traits<InputIt>::difference_type distance(InputIt a, InputIt b)
    {
        return detail::distance_helper<InputIt, typename iterator_traits<InputIt>::iterator_category>::distance(a, b);
    }

    template<class ForwardIt>
    ForwardIt next(ForwardIt it, typename iterator_traits<ForwardIt>::difference_type n = 1)
    {
        advance(it, n);
        return it;
    }
    template<class BidirIt>
    BidirIt prev(BidirIt it, typename iterator_traits<BidirIt>::difference_type n = 1)
    {
        advance(it, -n);
        return it;
    }

    //begin
    template<class C>
    constexpr auto begin(C& c) -> decltype(c.begin())
    {
        return c.begin();
    }
    template<class C>
    constexpr auto begin(C const& c) -> decltype(c.begin())
    {
        return c.begin();
    }
    template<class C>
    constexpr auto cbegin(C const& c) -> decltype(c.cbegin())
    {
        return c.cbegin();
    }
    template<class T, size_t N>
    T* begin(T (&array)[N])
    {
        return array;
    };
    //end
    template<class C>
    constexpr auto end(C& c) -> decltype(c.end())
    {
        return c.end();
    }
    template<class C>
    constexpr auto end(C const& c) -> decltype(c.end())
    {
        return c.end();
    }
    template<class C>
    constexpr auto cend(C const& c) -> decltype(c.cend())
    {
        return c.cend();
    }
    template<class T, size_t N>
    T* end(T (&array)[N])
    {
        return array + N;
    };
    //rbegin
    template<class C>
    constexpr auto rbegin(C& c) -> decltype(c.rbegin())
    {
        return c.rbegin();
    }
    template<class C>
    constexpr auto rbegin(C const& c) -> decltype(c.rbegin())
    {
        return c.rbegin();
    }
    template<class C>
    constexpr auto crbegin(C const& c) -> decltype(c.crbegin())
    {
        return c.crbegin();
    }
    //end
    template<class C>
    constexpr auto rend(C& c) -> decltype(c.rend())
    {
        return c.rend();
    }
    template<class C>
    constexpr auto rend(C const& c) -> decltype(c.rend())
    {
        return c.rend();
    }
    template<class C>
    constexpr auto crend(C const& c) -> decltype(c.crend())
    {
        return c.crend();
    }










}

