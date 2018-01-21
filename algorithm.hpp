

#pragma once
#include <stddef.h>
#include <stdint.h>
#include "iterator.hpp"
#include <type_traits>

namespace pstd {
    template<typename InputIter, typename UnaryPredicate>
    constexpr bool all_of(InputIter first, InputIter last, UnaryPredicate p )
    {
        static_assert(is_input_iterator<InputIter>::value, "Iterator must be an input iterator");

        while(first != last)
        {
            if(not p(*first)) return false;
            ++first;
        }
        return true;
    };

    template<typename InputIter, typename UnaryPredicate>
    constexpr bool any_of(InputIter first, InputIter last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIter>::value, "Iterator must be an input iterator");
        while(first != last)
        {
            if(p(*first)) return true;
            ++first;
        }
        return false;
    };

    template<typename InputIter, typename UnaryPredicate>
    constexpr bool none_of(InputIter first, InputIter last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIter>::value, "Iterator must be an input iterator");
        return not any_of(first, last, p);
    };

    template<typename InputIt, typename UnaryFunction>
    constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");
        while(first != last)
        {
            f(*first);
            ++first;
        }
        return move(f);
    };

    template<typename InputIt, typename T>
    constexpr typename iterator_traits<InputIt>::difference_type count(InputIt first, InputIt last, T const& value)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");

        typename iterator_traits<InputIt>::difference_type n = 0;
        while(first != last)
        {
            if(*first == last) n++;
            ++first;
        }
        return n;
    };

    template<typename InputIt, typename UnaryPredicate>
    constexpr typename iterator_traits<InputIt>::difference_type count_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");

        typename iterator_traits<InputIt>::difference_type n = 0;
        while(first != last)
        {
            auto const& val = *first;
            if(p(val)) n++;
            ++first;
        }
        return n;
    };

    template<typename InputIt1, typename InputIt2>
    constexpr pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");

        while(*first1 == *first2 and first1 != last1)
        {
            ++first1;
            ++first2;
        }
        return {first1, first2};
    };

    template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
    constexpr pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");

        while(p(*first1, *first2) and first1 != last1)
        {
            ++first1;
            ++first2;
        }
        return {first1, first2};
    };

    template<typename InputIt1, typename InputIt2>
    constexpr pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");

        while(*first1 == *first2 and first1 != last1 and first2 != last2)
        {
            ++first1;
            ++first2;
        }
        return {first1, first2};
    };

    template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
    constexpr pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");

        while(p(*first1, *first2) and first1 != last1 and first2 != last2)
        {
            ++first1;
            ++first2;
        }
        return {first1, first2};
    };

    //equal
    template<typename InputIt1, typename InputIt2>
    constexpr bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");
        return mismatch(first1, last1, first2).first == last1;
    };

    template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
    constexpr bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");
        return mismatch(first1, last1, first2, p).first == last1;
    };

    template<typename InputIt1, typename InputIt2>
    constexpr bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");
        auto res = mismatch(first1, last1, first2, last2);
        return res.first == last1 and res.second == last2;
    };

    template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
    constexpr bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");
        auto res = mismatch(first1, last1, first2, last2, p);
        return res.first == last1 and res.second == last2;
    };

    //find, find_if, find_if_not
    template<typename InputIt, typename T>
    constexpr InputIt find(InputIt first, InputIt last, T const& value)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");
        while(first != last and *first != value)
        {
            ++first;
        }
        return first;
    };

    template<typename InputIt, class UnaryPredicate>
    constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");
        while(first != last and not p(*first))
        {
            ++first;
        }
        return first;
    };
    template<typename InputIt, class UnaryPredicate>
    constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");
        while(first != last and p(*first))
        {
            ++first;
        }
        return first;
    };

    template<typename ForwardIt1, class ForwardIt2>
    constexpr ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "Iterator must be a forward input iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "Iterator must be a forward input iterator");

        ForwardIt1 found_location = last;
        auto slength = distance(s_first, s_last);
        if(slength == 0) return last;
        auto length = distance(first, last);
        if(length < slength) return last;

        auto search_last = first + (length - slength + 1);

        while(first != search_last)
        {
            if(mismatch(first, last, s_first, s_last).second == s_last) //no mismatch
            {
                return first;
            }
            ++first;
        }
        return last;
    };
    template<typename ForwardIt1, class ForwardIt2, class BinaryPredicate>
    constexpr ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "Iterator must be a forward input iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "Iterator must be a forward input iterator");

        ForwardIt1 found_location = last;
        auto slength = distance(s_first, s_last);
        if(slength == 0) return last;
        auto length = distance(first, last);
        if(length < slength) return last;

        auto search_last = first + (length - slength + 1);

        while(first != search_last)
        {
            if(mismatch(first, last, s_first, s_last, p).second == s_last) //no mismatch
            {
                return first;
            }
            ++first;
        }
        return last;
    };

    template<typename ForwardIt1, typename ForwardIt2>
    constexpr ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "Iterator must be a forward input iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "Iterator must be a forward input iterator");

        //for every element in [first, lat), use it as the search term in s_first, s_last

        while(first != last)
        {
            auto const& val = *first;
            auto it = find(s_first, s_last, val);
            if(it != s_last) return first;
            ++first;
        }
        return first;
    };

    template<typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
    constexpr ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "Iterator must be a forward input iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "Iterator must be a forward input iterator");

        //for every element in [first, lat), use it as the search term in s_first, s_last

        while(first != last)
        {
            auto const& val = *first;
            auto it = find(s_first, s_last, [&val, &p](auto const& v){return p(val, v);});
            if(it != s_last) return first;
            ++first;
        }
        return first;
    };

    //ajacent find: find two consecutive equal elements
    template<typename ForwardIt>
    constexpr ForwardIt ajacent_find(ForwardIt first, ForwardIt last)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward input iterator");
        if(first == last) return last;
        ForwardIt nextfirst = first + 1;
        while(nextfirst != last)
        {
            if(*nextfirst == *first) return first;
            ++nextfirst;
            ++first;
        }
        return last;
    }
    template<typename ForwardIt, typename BinaryPredicate>
    constexpr ForwardIt ajacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward input iterator");
        if(first == last) return last;
        ForwardIt nextfirst = first + 1;
        while(nextfirst != last)
        {
            if(p(*first, *nextfirst)) return first;
            ++nextfirst;
            ++first;
        }
        return last;
    }

    template <typename InputIt, typename OutputIt>
    constexpr OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be a input iterator");
        while(first != last)
        {
            *d_first = *first;
            ++d_first;
            ++first;
        }
        return d_first;
    };
    template <typename InputIt, typename OutputIt, class UnaryPredicate>
    constexpr OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be a input iterator");
        while(first != last)
        {
            if(p(*first))
            {
                *d_first = *first;
                ++d_first;
            }
            ++first;
        }
        return d_first;
    };
    template <typename InputIt, typename OutputIt>
    constexpr OutputIt copy_n(InputIt first, size_t count, OutputIt d_first)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be a input iterator");
        for(size_t i = 0; i < count; i++)
        {
            *d_first = *first;
            ++d_first;
            ++first;
        }
        return d_first;
    };

    template<typename BidirIt1, typename BidirIt2>
    constexpr BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
    {
        static_assert(is_bidirectional_iterator<BidirIt1>::value, "Iterator must be a bidirectional iterator");
        static_assert(is_bidirectional_iterator<BidirIt2>::value, "Iterator must be a bidirectional iterator");

        auto r_first = make_reverse_iterator(last);
        auto r_last = make_reverse_iterator(first);
        auto rd_first = make_reverse_iterator(d_last);

        auto res = copy(r_first, r_last, rd_first);
        return res.base();
    };

    template<typename InputIt, typename OutputIt>
    constexpr OutputIt move(InputIt first, InputIt last, OutputIt d_first)
    {
        static_assert(is_input_iterator<InputIt>::value, "first and last must be input iterators");

        while(first != last)
        {
            *d_first = move(*first);
            ++d_first;
            ++first;
        }
        return d_first;
    };
    template<typename InputIt, typename OutputIt>
    constexpr OutputIt move_backward(InputIt first, InputIt last, OutputIt d_last)
    {
        static_assert(is_input_iterator<InputIt>::value, "first and last must be input iterators");

        auto rfirst = make_reverse_iterator(last);
        auto rlast = make_reverse_iterator(first);
        auto rdfirst = make_reverse_iterator(d_last);

        auto res =  move(rfirst, rlast, rdfirst);
        return res.base();
    };

    template<typename ForwardIt, typename T>
    constexpr void fill(ForwardIt first, ForwardIt last, T const& value)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");

        while(first != last)
        {
            *first = value;
            ++first;
        }
    };
    template<typename ForwardIt, typename T>
    constexpr void fill_n(ForwardIt first, size_t n, T const& value)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");

        for(size_t i = 0; i < n; i++)
        {
            *first = value;
            ++first;
        }
    };

    //transform
    template<class InputIt, class OutputIt, class UnaryOperation>
    constexpr OutputIt transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation op)
    {
        static_assert(is_input_iterator<InputIt>::value, "first must be input iterator");
        while(first != last)
        {
            *d_first = op(*first);
            ++d_first;
            ++first;
        }
        return d_first;
    };

    template<class InputIt1, class InputIt2, class OutputIt, class BinaryOperation>
    constexpr OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOperation op)
    {
        static_assert(is_input_iterator<InputIt1>::value, "first1 must be input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "first2 must be input iterator");
        while(first1 != last1)
        {
            *d_first = op(*first1, *first2);
            ++d_first;
            ++first1;
            ++first2;
        }
        return d_first;
    };

    //generator
    template<class ForwardIt, class Generator>
    constexpr void generate(ForwardIt first, ForwardIt last, Generator gen)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        while(first != last)
        {
            *first = gen();
            ++first;
        }
    };
    //generator
    template<class ForwardIt, class Generator>
    constexpr void generate_n(ForwardIt first, size_t n, Generator gen)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        for(size_t i = 0; i < n; i++)
        {
            *first = gen();
            ++first;
        }
    };
    //remove, remove_if
    template<class ForwardIt, class T>
    constexpr ForwardIt remove(ForwardIt first, ForwardIt last, T const& value)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        //move the iterator forward until we find the first non-match.
        auto insert_point = find_if(first, last, [&value](auto const& v){return value != v;});
        if(insert_point == last) //no removals
        {
            return last;
        }
        first = insert_point + 1;
        while(first != last)
        {
            if(*first == value)
            {
                swap(*first, *insert_point);
                ++insert_point;
            }
            ++first;
        }
        return insert_point;
    };
    template<class ForwardIt, class UnaryPredicate>
    constexpr ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        //move the iterator forward until we find the first non-match.
        auto insert_point = find_if_not(first, last, p);
        if(insert_point == last) //no removals
        {
            return last;
        }
        first = insert_point + 1;
        while(first != last)
        {
            if(p(*first))
            {
                swap(*first, *insert_point);
                ++insert_point;
            }
            ++first;
        }
        return insert_point;
    };
    //remove_copy
    template<class InputIt, class OutputIt, class T>
    constexpr OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first, T const& value)
    {
        return copy_if(first, last, d_first, [&value](auto const& v){return v != value;});
    };

    template<class InputIt, class OutputIt, class UnaryPredicate>
    constexpr OutputIt remove_copy(InputIt first, InputIt last,OutputIt d_first, UnaryPredicate p)
    {
        return copy_if(first, last, d_first, [&p](auto const& v){return not p(v);});
    };

    template<class ForwardIt, class T>
    constexpr void replace(ForwardIt first, ForwardIt last, T const& old_value, T const& new_value)
    {
        while(first != last)
        {
            if(*first == old_value) *first = new_value;
            ++first;
        }
    };

    template<class ForwardIt, class UnaryPredicate, class T>
    constexpr void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p, T const& new_value)
    {
        while(first != last)
        {
            if(p(*first)) *first = new_value;
            ++first;
        }
    };

    template<class InputIt, class OutputIt, class T>
    constexpr OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first, T const& old_value, T const& new_value)
    {
        static_assert(is_input_iterator<first>::value, "first must be input iterator");
        while(first != last)
        {
            if(*first == old_value) *d_first = new_value;
            else *d_first = *first;
            ++d_first;
            ++first;
        }
        return d_first;
    };

    template<class InputIt, class OutputIt, class UnaryPredicate, class T>
    constexpr OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p, T const& new_value)
    {
        static_assert(is_input_iterator<InputIt>::value, "first must be input iterator");
        while(first != last)
        {
            if(p(*first)) *d_first = new_value;
            else *d_first = *first;
            ++d_first;
            ++first;
        }
        return d_first;
    };

    template<class ForwardIt1, class ForwardIt2>
    constexpr ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2 )
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "first1 must be forward iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "first2 must be forward iterator");
        while(first1 != last1)
        {
            swap(*first1, *first2);
            ++first1;
            ++first2;
        }
        return first2;
    };

    template<class ForwardIt1, class ForwardIt2>
    constexpr void iter_swap(ForwardIt1 a, ForwardIt2 b)
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "first1 must be forward iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "first2 must be forward iterator");
        if(a != b) swap(*a, *b);
    };

    template<class BidirIt>
    constexpr void reverse(BidirIt first, BidirIt last)
    {
        static_assert(is_bidirectional_iterator<BidirIt>::value, "first must be a bidirectional iterator");
        while((first != last) and (first != --last))
        {
            iter_swap(first, last);
            ++first;
        }
    }

    template<class BidirIt, class OutputIt>
    constexpr void reverse_copy(BidirIt first, BidirIt last, OutputIt d_first)
    {
        static_assert(is_bidirectional_iterator<BidirIt>::value, "first must be a bidirectional iterator");
        while(first != last)
        {
            *d_first = *(--last);
            ++d_first;
        }
        return d_first;
    };

    //rotate n_first left to first.
    template<class ForwardIt>
    constexpr ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        if(first == n_first) return last;
        if(n_first == last) return last;

        ForwardIt next = n_first;

        do
        {
            iter_swap(first, next);
            ++first;
            ++next;
            if(first == n_first) n_first = next;
        }
        while(next != last);

        ForwardIt ret = first;
        for(next = n_first; next != last; )
        {
            iter_swap(first, next);
            ++first;
            ++next;
            if(first == n_first) n_first = next;
            else if(next == last) next = n_first;
        }
        return ret;
    }

    template<class ForwardIt, class OutputIt>
    constexpr OutputIt rotate_copy(ForwardIt first, ForwardIt n_first, ForwardIt last, OutputIt d_first)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        d_first = copy(n_first, last, d_first);
        return copy(first, n_first, d_first);
    };

    //unique: collapse consecutive equal values
    template<class ForwardIt>
    ForwardIt unique(ForwardIt first, ForwardIt last)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be forward iterator");
        //find the first set of consecutve elements.
        auto last_insert = ajacent_find(first, last);
        if(last_insert == last) return last; //found no duplicates.
        //look forward until we find something not equal to last_insert
        first = last_insert + 1;
        while(first != last)
        {
            if(*first != *last_insert) //we've found something new, so move it down.
            {
                ++last_insert;
                *last_insert = move(*first);
            }
            ++first;
        }
        ++last_insert;
        return last_insert;
    }
    template<class ForwardIt, class BinaryPredicate>
    ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be forward iterator");
        //find the first set of consecutve elements.
        auto last_insert = ajacent_find(first, last, p);
        if(last_insert == last) return last; //found no duplicates.
        //look forward until we find something not equal to last_insert
        first = last_insert + 1;
        while(first != last)
        {
            if(not p(*first, *last_insert)) //we've found something new, so move it down.
            {
                ++last_insert;
                *last_insert = move(*first);
            }
            ++first;
        }
        ++last_insert;
        return last_insert;
    }












































}




