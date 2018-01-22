

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
        static_assert(is_input_iterator<InputIt>::value, "first must be input iterator");
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
    constexpr ForwardIt unique(ForwardIt first, ForwardIt last)
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
    constexpr ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
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
    template<class InputIt, class OutputIt>
    constexpr InputIt unique_copy(InputIt first, InputIt last, OutputIt d_first)
    {
        static_assert(is_input_iterator<InputIt>::value, " InputIt must be input iterator");
        auto last_unique= first;
        *d_first = *first;
        ++first;
        ++d_first;
        while(first != last)
        {
            if(*first != *last_unique)
            {
                *d_first = *first;
                ++d_first;
                last_unique = first;
            }
            ++first;
        }
        return d_first;
    };
    template<class InputIt, class OutputIt, class BinaryPredicate>
    constexpr InputIt unique_copy(InputIt first, InputIt last, OutputIt d_first, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, " InputIt must be input iterator");
        auto last_unique= first;
        *d_first = *first;
        ++first;
        ++d_first;
        while(first != last)
        {
            if(not p(*last_unique, *first))
            {
                *d_first = *first;
                ++d_first;
                last_unique = first;
            }
            ++first;
        }
        return d_first;
    };

    template<class InputIt, class UnaryPredicate>
    constexpr bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, " InputIt must be input iterator");
        if(first == last) return true;
        bool reached_partition = false; //set to true on the first false result.
        while(first != last)
        {
            auto res = p(*first);
            if(not res) reached_partition = true; //all elements following should be false.
            else if(reached_partition and res) //we had a false, then a true
                return false;
            ++first;
        }
        return true;
    };

    template<class ForwardIt, class UnaryPredicate>
    constexpr ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "ForwardIt must be a forward iterator");
        first = find_if_not(first, last, p);
        if(first == last) return first;

        for(auto i = next(first); i != last; ++i)
        {
            if(p(*i))
            {
                iter_swap(i, first);
                ++first;
            }
        }
        return first;
    };

    template<class InputIt, class OutputIt1, class OutputIt2, class UnaryPredicate>
    constexpr pair<OutputIt1, OutputIt2> partition_copy(
        InputIt first,
        InputIt last,
        OutputIt1 d_first_true,
        OutputIt1 d_first_false,
        UnaryPredicate p
    )
    {
        static_assert(is_input_iterator<InputIt>::value, " InputIt must be input iterator");
        while(first != last)
        {
            if(p(*first))
            {
                *d_first_true = move(*first);
                ++d_first_true;
            }
            else
            {
                *d_first_false = move(*first);
                ++d_first_false;

            }
            ++first;
        }
        return {d_first_true, d_first_false};
    };

    template<class BidirIt, class UnaryPredicate>
    constexpr BidirIt stable_partition(BidirIt first, BidirIt last, UnaryPredicate p)
    {
        static_assert(is_bidirectional_iterator<BidirIt>::value, "BidirIt must be a bidirectional iterator");

        //probably a bad implementation, but whatever
        first = find_if_not(first, last, p); //find the first false value.
        if(first == last) return  last;
        //now walk i forward until another true value is found. When it is found, rotate the remaining set so
        //that this element is in position first.
        auto i = first+1;
        while(i != last)
        {
            if(p(*i)) //we found another true, so rotate i into first.
            {
                rotate(first, i, last);
                first = find_if_not(first, last, p);
                i = first + 1;
                continue;
            }
            ++i;
        }
        return first;
    };

    namespace detail
    {
        template<class ForwardIt, class UnaryPredicate, bool IsRandomAccess>
        struct partition_point_helper
        {
            constexpr static ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPredicate p)
            {
                while(first != last)
                {
                    if(not p(*first)) return first;
                    ++first;
                }
                return first;
            }

        };

        //specialization for random access iterators: can do a binary search for the partition point.
        template<class RandomIt, class UnaryPredicate>
        struct partition_point_helper<RandomIt, UnaryPredicate, true>
        {
            constexpr static RandomIt partition_point(RandomIt first, RandomIt last, UnaryPredicate p)
            {

                while(first != last)
                {
                    auto i = first + distance(first, last) / 2;
                    //branch on i
                    if(p(*i)) //predicate is true, so we must look in the upper half.
                    {
                        first = i + 1;
                        //last = last;
                        continue;
                    }
                    else //predicate is false, so we must look in the lower half.
                    {
                        //first = first;
                        last = i;
                        continue;
                    }
                }
                //first and last are both pointing toward the partition point;
                return first;
            }
        };
    }

    //requires range be partitioned.
    template<class ForwardIt, class UnaryPredicate>
    constexpr ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward iterator");
        return detail::partition_point_helper<
            ForwardIt,
            UnaryPredicate,
            is_random_access_iterator<ForwardIt>::value
        >::partition_point(first, last, p);
    };

    template<class ForwardIt>
    constexpr ForwardIt is_sorted_until(ForwardIt first, ForwardIt last)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward iterator");

        auto i = next(first);

        while(i != last)
        {
            if(not (*first < *i)) return i;
            ++first;
            ++i;
        }
        return i;
    }
    template<class ForwardIt, class Compare>
    constexpr ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward iterator");

        auto i = next(first);

        while(i != last)
        {
            if(not comp(*first,  *i)) return i;
            ++first;
            ++i;
        }
        return i;
    };
    template<class ForwardIt>
    constexpr bool is_sorted(ForwardIt first, ForwardIt last)
    {
        return is_sorted_until(first, last) == last;
    }
    template<class ForwardIt, class Compare>
    constexpr bool is_sorted(ForwardIt first, ForwardIt last, Compare comp)
    {
        return is_sorted_until(first, last, comp) == last;
    };

    //standard quicksort.
    template<class RandomIt>
    void sort(RandomIt first, RandomIt last)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(is_sorted(first, last)) return; //no use sorting a sorted array

        auto pivot = *next(first,  distance(first, last)/2);
        auto middle1 = partition(first, last, [&pivot](auto const& element){return element < pivot;});
        auto middle2 = partition(middle1, last, [&pivot](auto const& element){return not(pivot < element);});
        sort(first, middle1);
        sort(middle2, last);
    }

    template<class RandomIt, class Compare>
    void sort(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(is_sorted(first, last)) return; //no use sorting a sorted array

        auto pivot = *next(first,  distance(first, last)/2);
        auto middle1 = partition(first, last, [&pivot, &comp](auto const& element){return comp(element, pivot);});
        auto middle2 = partition(middle1, last, [&pivot, &comp](auto const& element){return not comp(pivot, element);});
        sort(first, middle1);
        sort(middle2, last);
    };



    //check for max heap.
    template<class RandomIt>
    RandomIt is_heap_until(RandomIt first, RandomIt last)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        const auto N = distance(first, last);

        //heap property: h[i-1/2] >= h[i]
        size_t i = 1;
        for(; i < N; i++) //don't have to check root since it doesn't have a parent.
        {
            size_t parent = (i-1)/2;

            if(*(first + parent) < *(first + i)) return (first + i);
        }
        return (first + i);
    }
    template<class RandomIt, class Compare>
    RandomIt is_heap_until(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        const auto N = distance(first, last);

        //heap property: h[i-1/2] >= h[i]
        size_t i = 1;
        for(; i < N; i++) //don't have to check root since it doesn't have a parent.
        {
            size_t parent = (i-1)/2;

            if(comp(*(first + parent), *(first + i))) return (first + i);
        }
        return (first + i);
    }

    template<class RandomIt>
    bool is_heap(RandomIt first, RandomIt last)
    {
        return is_heap_until(first, last) == last;
    };

    template<class RandomIt, class Compare>
    bool is_heap(RandomIt first, RandomIt last, Compare comp)
    {
        return is_heap_until(first, last, comp) == last;
    };

    //element last-1 is the element to insert.
    template<class RandomIt>
    void push_heap(RandomIt first, RandomIt last)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(next(first) == last) return;
        auto elem = last-1;
        while(elem != first)
        {
            const auto parent = first + (distance(first, elem) - 1)/2; parent != first;
            //compare with parent
            if(*parent < *elem)
            {
                iter_swap(parent, elem);
                elem = parent;
                continue;
            }
            else
            {
                break;
            }
        }
    }
    template<class RandomIt, class Compare>
    void push_heap(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(next(first) == last) return;
        auto elem = last-1;
        while(elem != first)
        {
            const auto parent = first + (distance(first, elem) - 1)/2; parent != first;
            //compare with parent
            if(comp(*parent, *elem))
            {
                iter_swap(parent, elem);
                elem = parent;
                continue;
            }
            else
            {
                break;
            }
        }
    };

    template<class RandomIt>
    void make_heap(RandomIt first, RandomIt last)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");

        auto heap_end = first + 1; //start with one-element heap.

        while(heap_end != last)
        {
            ++heap_end;  //add next element onto bottom of heap.
            push_heap(first, heap_end);
        }
    }

    template<class RandomIt, class Compare>
    void make_heap(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");

        auto heap_end = first + 1; //start with one-element heap.

        while(heap_end != last)
        {
            ++heap_end;  //add next element onto bottom of heap.
            push_heap(first, heap_end, comp);
        }
    };

    namespace detail
    {
        //percolate the value at the top of the heap down until it lies in its proper position.
        template<class RandomIt, class Compare>
        void percolate_heap(RandomIt first, RandomIt last, Compare comp)
        {
            auto elem = first;
            //left child is  2i, right child is 2i+1;
            while(distance(elem, last) > 2 * distance(first, elem))
            {
                auto elem_index = distance(first, elem);
                auto left_child = first +  2 * elem_index;
                auto right_child = first + (2 * elem_index + 1);

                auto swap_location = elem;
                if((*elem < *left_child)) swap_location = left_child;
                if(right_child != last)
                {
                    if(comp(*elem, *right_child) and comp(*left_child, *right_child)) swap_location = right_child;
                }
                if(swap_location != elem)
                {
                    iter_swap(elem, swap_location);
                    elem = swap_location;
                    continue;
                }
            }
        };
    }

    template<class RandomIt>
    void pop_heap(RandomIt first, RandomIt last)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(first == last-1) return;

        //replace root with the last element
        --last;
        iter_swap(first, last);
        detail::percolate_heap(first, last, operator<);
    }
    template<class RandomIt, class Compare>
    void pop_heap(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(first == last-1) return;

        //replace root with the last element
        --last;
        iter_swap(first, last);
        detail::percolate_heap(first, last, comp);
    }

    template<class RandomIt>
    void sort_heap(RandomIt first, RandomIt last)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        while(first != last)
        {
            pop_heap(first, last);
            --last;
        }
    }

    template<class RandomIt, class Compare>
    void sort_heap(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        while(first != last)
        {
            pop_heap(first, last, comp);
            --last;
        }
    };

    template<class RandomIt>
    void partial_sort(RandomIt first, RandomIt middle, RandomIt last)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(middle == first) return;
        if(middle == last) sort(first, last);

        auto rfirst = make_reverse_iterator(last);
        auto rlast = make_reverse_iterator(first);
        auto rmiddle = make_reverse_iterator(middle);
        auto mdist = distance(first, middle);

        auto compare = [](auto const& a, auto const& b){return not (a < b);};

        make_heap(rfirst, rlast, compare);

        for(size_t i = 0; i < mdist; i++)
        {
            pop_heap(rfirst, rlast, compare);
        }
    }
    template<class RandomIt, class Compare>
    void partial_sort(RandomIt first, RandomIt middle, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(middle == first) return;
        if(middle == last) sort(first, last);

        auto rfirst = make_reverse_iterator(last);
        auto rlast = make_reverse_iterator(first);
        auto rmiddle = make_reverse_iterator(middle);
        auto mdist = distance(first, middle);

        auto compare = [&comp](auto const& a, auto const& b){return not comp(a, b);};

        make_heap(rfirst, rlast, compare);

        for(size_t i = 0; i < mdist; i++)
        {
            pop_heap(rfirst, rlast, compare);
        }
    }

    //heapsort here.
    template<class InputIt, class RandomIt>
    RandomIt partial_sort_copy(InputIt first, InputIt last, RandomIt d_first, RandomIt d_last)
    {
        static_assert(is_input_iterator<InputIt>::value, "first&last must be input iterators");
        static_assert(is_random_access_iterator<RandomIt>::value, "d_first and d_last must be random access iterators.");
        if(first == last) return d_first;
        if(d_first == d_last) return d_first;

        auto dsize = distance(d_first, d_last);
        auto heap_end = d_first;
        //push some values into
        while(first != last and heap_end != d_last)
        {
            *heap_end = *first;
            ++first;
            ++heap_end;
        }
        make_heap(d_first, heap_end);
        //result is now a maximal heap. So if we replace the top(front) element and percolate, then
        //eventually the largest elements will be removed.
        while(first != last)
        {
            if(*first < *d_first)
            {
                *d_first = *first;
                detail::percolate_heap(d_first, heap_end, operator<);

            }
            ++first;
        }
        sort_heap(d_first, heap_end);
        return heap_end;
    };
    template<class InputIt, class RandomIt, class Compare>
    RandomIt partial_sort_copy(InputIt first, InputIt last, RandomIt d_first, RandomIt d_last, Compare comp)
    {
        static_assert(is_input_iterator<InputIt>::value, "first&last must be input iterators");
        static_assert(is_random_access_iterator<RandomIt>::value, "d_first and d_last must be random access iterators.");
        if(first == last) return d_first;
        if(d_first == d_last) return d_first;

        auto dsize = distance(d_first, d_last);
        auto heap_end = d_first;
        //push some values into
        while(first != last and heap_end != d_last)
        {
            *heap_end = *first;
            ++first;
            ++heap_end;
        }
        make_heap(d_first, heap_end);
        //result is now a maximal heap. So if we replace the top(front) element and percolate, then
        //eventually the largest elements will be removed.
        while(first != last)
        {
            if(*first < *d_first)
            {
                *d_first = *first;
                detail::percolate_heap(d_first, heap_end, comp);

            }
            ++first;
        }
        sort_heap(d_first, heap_end);
        return heap_end;
    };

    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        static_assert(is_input_iterator<InputIt1>::value, "InputIt1 must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "InputIt2 must be an input iterator");

        while(first1 != last1 and first2 != last2)
        {
            if(comp(*first1, *first2))
            {
                *d_first = *first1;
                ++first1;
            }
            else
            {
                *d_first = *first2;
                ++first2;
            }
            ++d_first;
        }
        //at least one of either range 1 or two is now empty.
        if(first1 != last1)
        {
            d_first = copy(first1, last1, d_first);
        }
        else if(first2 != last2)
        {
            d_first = copy(first2, last2, d_first);
        }
        return d_first;
    };
    template<class InputIt1, class InputIt2, class OutputIt>
    OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return merge(first1, last1, first2, last2, d_first, operator<);
    };

    template<class BidirIt, class Compare>
    void inplace_merge(BidirIt first, BidirIt midpoint, BidirIt last, Compare comp)
    {
        static_assert(is_bidirectional_iterator<BidirIt>::value, "Iterator must be bidirectional iterator");
        //mergesort: split the range in half, mergesort the first half, and mergesort the second half.
        auto d = distance(first, last);
        if(d == 0) return; //base case: no elements are alway sorted
        if(d == 1) return; //a single element is always sorted.
        if(d == 2)
        {
            if(comp(*(first+1), *(first) ))
            {
                iter_swap(first, (first+1));
            }
        }
        auto ip = first;
        auto rbuf = midpoint;
        while(distance(ip, midpoint) > 0)
        {
            if(not comp(*ip, *rbuf)) //insert from right subgroup
            {
                iter_swap(ip, rbuf);
                ++ip;
                ++rbuf;
            }
            else //insert from left subgroup
            {
                if(midpoint == rbuf)
                {
                    //we havent' moved anything from lbuf over yet, so everything is in the right order.
                    ++ip;
                }
                else
                {
                    iter_swap(ip, midpoint);
                    ++ip;
                }
            }
        }
        if(rbuf == midpoint) //special case, whole merge was from the left side, so the right side is already soreted
        {
            return;
        }
        //now [mid, rbuf) is still sorted in the original order, and so is [rbuf, last)
        inplace_merge(ip, rbuf, last, comp);
    }
    template<class BidirIt>
    void inplace_merge(BidirIt first, BidirIt midpoint, BidirIt last)
    {
        return inplace_merge(first, midpoint, last, operator<);
    };

    //use mergesort, with a temporary buffer for the displaced element.
    template<class RandomIt, class Compare>
    void stable_sort(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "first, last must be random access iterators.");
        auto d = distance(first, last);
        if(d == 0) return; //base case: no elements are alway sorted
        if(d == 1) return; //a single element is always sorted.
        if(d == 2)
        {
            if(comp(*(first+1), *(first) ))
            {
                iter_swap(first, (first+1));
            }
        }
        auto midpoint = first + (d/2);
        stable_sort(first, midpoint, comp);
        stable_sort(midpoint, last, comp);
        inplace_merge(first, midpoint, last, comp);
    }

    template<class RandomIt>
    void stable_sort(RandomIt first, RandomIt last)
    {
        return stable_sort(first, last, operator<);
    }

    namespace detail
    {
        template<class BidirIt, class Compare>
        BidirIt median_of_three(BidirIt first, BidirIt last, Compare comp)
        {
            static_assert(is_forward_iterator<BidirIt>::value, "first, last must be forward iterators");
            auto a = first;
            auto b = next(first, distance(first, last)/2);
            auto c = prev(last);

            if(comp(*b, *a)) swap(a, b); //now a <= b
            if(comp(*c, *b))
            {
                swap(c, b); //now b < c
                if(comp(*b, *a)) swap(a, b); //now a < b

            }
            return b;
        };
    }

    template<class RandomIt, class Compare>
    void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "first, last must be random access iterators.");
        if(first == last) return;
        if(nth == last) return;
        //partition the range
        while(last - first > 3)
        {
            auto median = detail::median_of_three(first, last, comp);
            auto cut = partition(first, last, [&median, &comp](auto const& val){return comp(*median, val);});
            if(cut <= nth) first = cut;
            else last = cut;
        }
        //3-way insertion sort.
        auto ip = first;
        while(ip != prev(last))
        {
            auto best = ip+1;
            first = best;
            while(first != last)
            {
                if(comp(*first, *best)) best = first;
                ++first;
            }
            if(comp(*best, *ip)) iter_swap(ip, best);
            ++ip;
        }
    };
    template<class RandomIt>
    void nth_element(RandomIt first, RandomIt nth, RandomIt last)
    {
        return nth_element(first, nth, last, operator<);
    }

    template<class ForwardIt, class T>
    ForwardIt lower_bound(ForwardIt first, ForwardIt last, T  const& val)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward iterator");
        auto count = distance(first, last);
        while(count > 0)
        {
            auto it = first;
            auto step = count/2;
            advance(it, step);
            if(*it < val)
            {
                first = ++it;
                count -= step + 1;

            }
            else
                count = step;
        }
        return first;
    };
    template<class ForwardIt, class T, class Compare>
    ForwardIt lower_bound(ForwardIt first, ForwardIt last, T  const& val, Compare comp)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward iterator");
        auto count = distance(first, last);
        while(count > 0)
        {
            auto it = first;
            auto step = count/2;
            advance(it, step);
            if(comp(*it, val))
            {
                first = ++it;
                count -= step + 1;

            }
            else
                count = step;
        }
        return first;
    };
    template<class ForwardIt, class T>
    ForwardIt upper_bound(ForwardIt first, ForwardIt last, T  const& val)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward iterator");
        auto count = distance(first, last);
        while(count > 0)
        {
            auto it = first;
            auto step = count / 2;
            advance(it, step);
            if(not(val < *it))
            {
                first = ++it;
                count -= step + 1;
            }
            else
                count = step;
        }
        return first;
    };
    template<class ForwardIt, class T, class Compare>
    ForwardIt upper_bound(ForwardIt first, ForwardIt last, T  const& val, Compare comp)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward iterator");
        auto count = distance(first, last);
        while(count > 0)
        {
            auto it = first;
            auto step = count / 2;
            advance(it, step);
            if(not comp(val, *it))
            {
                first = ++it;
                count -= step + 1;
            }
            else
                count = step;
        }
        return first;
    };

    template<class ForwardIt, class T>
    bool binary_search(ForwardIt first, ForwardIt last, T const& value)
    {
        first = lower_bound(first, last, value);
        return (not(first == last) and not (value < *first));
    };

    template<class ForwardIt, class T, class Compare>
    bool binary_search(ForwardIt first, ForwardIt last, T const& value, Compare comp)
    {
        first = lower_bound(first, last, value, comp);
        return (not(first == last) and not comp(value, *first));
    };

    template<class ForwardIt, class T>
    pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last, T const& value)
    {
        return {lower_bound(first, last, value), upper_bound(first, last, value)};
    };
    template<class ForwardIt, class T, class Compare>
    pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last, T const& value, Compare comp)
    {
        return {lower_bound(first, last, value, comp), upper_bound(first, last, value, comp)};
    };

    template<class InputIt1, class InputIt2, class Compare>
    constexpr bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        static_assert(is_input_iterator<InputIt1>::value, "first1 and last1 must be input iterators");
        static_assert(is_input_iterator<InputIt2>::value, "first2 and last2 must be input iterators");
        for(;first2 != last2; ++first1)
        {
            if(first1 == last1 or comp(*first2, *first1))
            {
                return false;
            }
            if(not comp(*first1, *first2)) ++first2;
        }
        return true;
    };

    template<class InputIt1, class InputIt2>
    constexpr bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        return includes(first1, last1, first2, last2, operator<);
    };

    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while(first1 != last1)
        {
            if(first2 == last2) return copy(first1, last1, d_first);
            if(comp(*first1, *first2))
            {
                *d_first = *first1;
                ++d_first;
                ++first1;
            }
            else
            {
                if(not comp(*first2, *first1))
                {
                    ++first1;
                }
                ++first2;
            }

        }
        return d_first;
    };
    template<class InputIt1, class InputIt2, class OutputIt>
    constexpr OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return set_difference(first1, last1, first2, last2, d_first, operator<);
    };
    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while(first1 != last1 and first2 != last2)
        {
            if(comp(*first1, first2))
            {
                ++first1;
            }
            else
            {
                if( not comp(*first2, *first1))
                {
                    *d_first = *first1;
                    ++d_first;
                    ++first1;
                }
                ++first2;
            }
        }
        return d_first;
    };
    template<class InputIt1, class InputIt2, class OutputIt>
    constexpr OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return set_intersection(first1, last1, first2, last2, d_first, operator<);
    };
    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while(first1 != last1)
        {
            if(first2 == last2) return copy(first1, last1, d_first);
            if(comp(*first1, *first2))
            {
                *d_first = *first1;
                ++first1;
                ++d_first;
            }
            else
            {
                if(comp(*first2, *first1))
                {
                    *d_first = *first2;
                    ++d_first;
                }
                else
                {
                    ++first1;
                }
                ++first2;
            }
        }
        return copy(first2, last2, d_first);
    };
    template<class InputIt1, class InputIt2, class OutputIt>
    constexpr OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return set_symmetric_difference(first1, last1, first2, last2, d_first, operator<);
    };
    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        for(; first1 != last1; ++d_first)
        {
            if(first2 == last2) return copy(first1, last1, d_first);

            if(comp(*first2, *first1))
            {
                *d_first = *first2;
                ++d_first;
                ++first2;
            }
            else
            {
                *d_first = *first2;
                ++first2;
                if(not comp(*first1, *first2))
                {
                    ++first2;
                }
                ++first1;
            }
        }
        return  copy(first2, last2, d_first);
    };
    template<class InputIt1, class InputIt2, class OutputIt>
    constexpr OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return set_union(first1, last1, first2, last2, d_first, operator<);
    };

    template<class T>
    constexpr T const& clamp(T const& v, T const& low, T const& high)
    {
        return (v < low) ? low : (high < v) ? high : v;
    }

    template<class T, class Compare>
    constexpr T const& clamp(T const& v, T const& low, T const& high, Compare comp)
    {
        return comp(v, low) ? low : comp(high, v) ? high : v;
    };

    template<class T>
    constexpr T const& max(T const& a, T const& b)
    {
        return (a < b) ? b : a;
    }
    template<class T, class Compare>
    constexpr T const& max(T const& a, T const& b, Compare comp)
    {
        return (comp(a, b) ? b : a);
    };
    template<class T>
    constexpr T const& min(T const& a, T const& b)
    {
        return (a < b) ? a : b;
    }
    template<class T, class Compare>
    constexpr T const& min(T const& a, T const& b, Compare comp)
    {
        return (comp(a, b) ? a : b);
    };

    template<typename T>
    constexpr pair<T const&, T const&> minmax(T const& a, T const& b)
    {
        using R = pair<T const&, T const&>;
        return (a < b) ? R{a, b} : R{b, a};
    };
    template<typename T, typename Compare>
    constexpr pair<T const&, T const&> minmax(T const& a, T const& b, Compare comp)
    {
        using R = pair<T const&, T const&>;
        return comp(a, b) ? R{a, b} : R{b, a};
    };

    template<class ForwardIt, class Compare>
    constexpr ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp)
    {
        if(first == last) return {first, first};
        auto ret = first;
        ++first;
        while(first != last)
        {
            if(comp(*ret, *first))
            {
                ret = first;
            }
            ++first;
        }
        return ret;
    }
    template<class ForwardIt>
    constexpr ForwardIt max_element(ForwardIt first, ForwardIt last)
    {
        return max_element(first, last, operator<);
    }
    template<class ForwardIt, class Compare>
    constexpr ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)
    {
        if(first == last) return {first, first};
        auto ret = first;
        ++first;
        while(first != last)
        {
            if(comp(*first, *ret))
            {
                ret = first;
            }
            ++first;
        }
        return ret;
    }
    template<class ForwardIt>
    constexpr ForwardIt min_element(ForwardIt first, ForwardIt last)
    {
        return min_element(first, last, operator<);
    }

    template<class ForwardIt, class Compare>
    constexpr pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last, Compare comp)
    {
        if(first == last) return {first, first};
        pair<ForwardIt, ForwardIt> ret = {first, first};
        ++first;
        while(first != last)
        {
            if(comp(*first, *ret.first))
            {
                ret.first = first;
            }
            if(comp(*ret.second, *first))
            {
                ret.second = first;
            }
            ++first;
        }
        return ret;
    };
    template<class ForwardIt>
    constexpr pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last)
    {
        return minmax_element(first, last, operator<);
    };
    template<class InputIt1, class InputIt2, class Compare>
    bool lexographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        while(first1 != last1 and first2 != last2)
        {
            if(comp(*first1, *first2)) return true;
            else if(comp(*first2, *first1)) return false;
            ++first1;
            ++first2;
        }
        //at least one of the ranges has ended.
        return (first1 == last1 and first2 != last2);
    };
    template<class InputIt1, class InputIt2>
    bool lexographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        return lexographical_compare(first1, last1, first2, last2, operator<);
    };
    //todo: permutations.
};




