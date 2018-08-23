

#pragma once
#include <stddef.h>
#include <stdint.h>
#include "iterator.hpp"
#include "pstdlib_namespace.hpp"
#include "type_traits.hpp"

namespace PSTDLIB_NAMESPACE {

    namespace detail
    {
        // helper functors that perform equal, greater, and less operations on the underlying values.
        struct equal
        {
            template<class Lhs, class Rhs>
            bool operator()(Lhs const& lhs, Rhs const& rhs) const
            {
                return lhs == rhs;
            }
        };

        struct less
        {
            template<class Lhs, class Rhs>
            bool operator()(Lhs const& lhs, Rhs const& rhs) const
            {
                return lhs < rhs;
            }
        };

        struct greater
        {
            template<class Lhs, class Rhs>
            bool operator()(Lhs const& lhs, Rhs const& rhs) const
            {
                return lhs > rhs;
            }
        };

        template<typename BinaryPredicate, typename InputIt1, typename InputIt2>
        constexpr static bool is_binary_predicate_v = is_invocable_r<
            BinaryPredicate,
            bool,  // result convertible to bool
            typename iterator_traits<InputIt1>::value_type const&, //takes references to iterator values types.
            typename iterator_traits<InputIt2>::value_type const&
        >::value;

        template<typename UnaryPredicate, typename InputIt>
        constexpr static bool is_unary_predicate_v = is_invocable_r<
            UnaryPredicate,
            bool,
            typename iterator_traits<InputIt>::value_type const&
        >::value;

    }

    /**
     * Checks that a  unary predicate returns true for all items in range [first, last)
     * @tparam InputIter The type fo the input itator.
     * @tparam UnaryPredicate predicate type
     * @param first first element in range
     * @param last end of element range.
     * @param p Predicate to evaluate. Must be callable with InputIter::value_type.
     */
    template<typename InputIter, typename UnaryPredicate>
    constexpr bool all_of(InputIter first, InputIter last, UnaryPredicate p )
    {
        static_assert(is_input_iterator<InputIter>::value, "Iterator must be an input iterator");

        while(not(first == last))
        {
            if(not p(*first)) return false;
            ++first;
        }
        return true;
    };

    /**
     * Checks that a unary predicate returns true for at least one item in [first, last)
     * @tparam InputIter The type fo the input itator.
     * @tparam UnaryPredicate predicate type
     * @param first first element in range
     * @param last end of element range.
     * @param p Predicate to evaluate. Must be callable with InputIter::value_type.
     */
    template<typename InputIter, typename UnaryPredicate>
    constexpr bool any_of(InputIter first, InputIter last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIter>::value, "Iterator must be an input iterator");
        while(not(first == last))
        {
            if(p(*first)) return true;
            ++first;
        }
        return false;
    };

    /**
     * Checks that a unary predicate returns true for none of the elements in [first, last)
     * @tparam InputIter The type fo the input itator.
     * @tparam UnaryPredicate predicate type
     * @param first first element in range
     * @param last end of element range.
     * @param p Predicate to evaluate. Must be callable with InputIter::value_type.
     */
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
        while(not(first == last))
        {
            f(*first);
            ++first;
        }
        return move(f);
    };

    /**
     * Count the number of items that satisfy the unary predicate p.
     */
    template<typename InputIt, typename UnaryPredicate>
    constexpr typename iterator_traits<InputIt>::difference_type count_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");

        typename iterator_traits<InputIt>::difference_type n = 0;
        while(not(first == last))
        {
            auto const& val = *first;
            if(p(val)) n++;
            ++first;
        }
        return n;
    };

    /**
     * Count the number of items in the input range that compare equal to value.
     * @param value The value to count.
     */
    template<typename InputIt, typename T>
    constexpr typename iterator_traits<InputIt>::difference_type count(InputIt first, InputIt last, T const& value)
    {
        return count_if(first, last, [&value](auto const& v){return v == value;});
    };


    /**
     * Find the first position where two ranges differ.
     * @tparam InputIt1 Type of the first input range iterator
     * @tparam InputIt2 Type of the second input range iterator.
     * @tparam BinaryPredicate A callable with signature compatible to
     *      bool(InputIt1::value_type const&, InputIt2::value_type const&)
     * @param first1 Start of first range
     * @param last1 End of first range
     * @param first2 Start of second range
     * @param p Binary predicate to apply
     * @return A pair of iterators indicating the first mismatched position in ranges 1 and 2, respectively. If the
     *      ranges are equivalent, then a pair of {last1, first2 + (last1-first1)} will be returned.
     */
    template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
    constexpr pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");

        while(p(*first1, *first2) and not(first1 == last1))
        {
            ++first1;
            ++first2;
        }
        return {first1, first2};
    };

    /**
     * Find the first differing position in two ranges. The equality operator is used.
     */
    template<typename InputIt1, typename InputIt2>
    constexpr pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        return mismatch(first1, last1, first2, detail::equal());
    };


    template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
    constexpr pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");

        while(p(*first1, *first2) and not(first1 == last1) and not(first2 == last2))
        {
            ++first1;
            ++first2;
        }
        return {first1, first2};
    };

    template<typename InputIt1, typename InputIt2>
    constexpr pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        return mismatch(first1, last1, first2, last2, detail::equal());
    };


    //equal
    template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
    constexpr bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");
        return mismatch(first1, last1, first2, p).first == last1;
    };
    template<typename InputIt1, typename InputIt2>
    constexpr bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        static_assert(is_input_iterator<InputIt1>::value, "Iterator must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "Iterator must be an input iterator");
        return mismatch(first1, last1, first2).first == last1;
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
    template<typename InputIt, class UnaryPredicate>
    constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");
        while(not(first == last) and not p(*first))
        {
            ++first;
        }
        return first;
    };

    template<typename InputIt, class UnaryPredicate>
    constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be an input iterator");
        while(not(first == last) and p(*first))
        {
            ++first;
        }
        return first;
    };

    template<typename InputIt, typename T>
    constexpr InputIt find(InputIt first, InputIt last, T const& value)
    {
        return find_if(first, last, [&value](auto const& v){return v == value;});
    };


    //find the last subsequence of [s_first, s_last) in [first, last).
    // if not found, return last, otherwise iterator to beginning of sequence.
    /**
     * Find the first sequence of [s_first, s_last) in [first, last).
     * @tparam ForwardIt1 Iterator type for search range
     * @tparam ForwardIt2  Iterator type for needle range
     * @tparam BinaryPredicate An operation to compare elements of the search and needle range.
     * @param first First element of the search range
     * @param last End fo teh search range
     * @param s_first First element of the needle range
     * @param s_last End of the needle range
     * @param p Function to compare search and needle elements.
     * @return  If the subsequence is found, then return an iterator to the first element of the sequence. Otherwise, if
     * the sequence is not found, return last. If the size of [s_first, s_last) is zero, then last is returned. If the
     * size of the needle range is larger than the search range, then return last.
     */
    template<typename ForwardIt1, class ForwardIt2, class BinaryPredicate>
    constexpr ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "Iterator must be a forward input iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "Iterator must be a forward input iterator");

        ForwardIt1 found_location = last; // if we don't find anything then return last.
        auto slength = distance(s_first, s_last);
        if(slength == 0) return last;

        auto length = distance(first, last);
        if(length < slength) return last;

        auto search_last = first + (length - slength + 1);

        while(not(first == search_last))
        {
            if(mismatch(first, last, s_first, s_last, p).second == s_last) //no mismatch
            {
                found_location = first;
            }
            ++first;
        }

        return found_location;
    };
    template<typename ForwardIt1, class ForwardIt2>
    constexpr ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
    {
        return find_end(first, last, s_first, s_last, detail::equal());
    };

    template<typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
    constexpr ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "Iterator must be a forward input iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "Iterator must be a forward input iterator");

        //for every element in [first, lat), use it as the search term in s_first, s_last

        while(not(first == last))
        {
            auto const& val = *first;
            auto it = find_if(s_first, s_last, [&val, &p](auto const& v){return p(val, v);});
            if(not(it == s_last)) return first;
            ++first;
        }
        return first;
    };

    template<typename ForwardIt1, typename ForwardIt2>
    constexpr ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
    {
        return find_first_of(first, last, s_first, s_last, detail::equal());
    };


    //ajacent find: find two consecutive equal elements
    template<typename ForwardIt, typename BinaryPredicate>
    constexpr ForwardIt ajacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward input iterator");
        if(first == last) return last;
        ForwardIt nextfirst = first + 1;
        while(not(nextfirst == last))
        {
            if(p(*first, *nextfirst)) return first;
            ++nextfirst;
            ++first;
        }
        return last;
    }
    template<typename ForwardIt>
    constexpr ForwardIt ajacent_find(ForwardIt first, ForwardIt last)
    {
        return ajacent_find(first, last, detail::equal());
    }

    template <typename InputIt, typename OutputIt>
    constexpr OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
    {
        static_assert(is_input_iterator<InputIt>::value, "Iterator must be a input iterator");
        while(not(first == last))
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
        while(not(first == last))
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

        while(not(first == last))
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

        while(not(first == last))
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
        while(not(first == last))
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
        while(not(first1 == last1))
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
        while(not(first == last))
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
    template<class ForwardIt, class UnaryPredicate>
    constexpr ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p )
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        first = find_if(first, last, p);
        if (not(first == last))
            for(ForwardIt i = first; not(++i == last); )
                if (!p(*i))
                    *first++ = move(*i);
        return first;
    };
    template<class ForwardIt, class T>
    constexpr ForwardIt remove(ForwardIt first, ForwardIt last, T const& value)
    {
        return remove_if(first, last, [&value](auto const& v){return v == value;});
    };

    //remove_copy
    template<class InputIt, class OutputIt, class UnaryPredicate>
    constexpr OutputIt remove_copy_if(InputIt first, InputIt last,OutputIt d_first, UnaryPredicate p)
    {
        return copy_if(first, last, d_first, [&p](auto const& v){return not p(v);});
    };
    template<class InputIt, class OutputIt, class T>
    constexpr OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first, T const& value)
    {
        return copy_if(first, last, d_first, [&value](auto const& v){return not(v == value);});
    };


    /**
     * Replace all values in [first, last) for which the predicate p returns true with new_value.
     * @tparam ForwardIt Iterator type
     * @tparam UnaryPredicate Predicate function type
     * @tparam T Value type. Iterator type must be dereference-assignable by T.
     * @param first Start of range
     * @param last End of range
     * @param p Predicate function. Return value must be coercible to bool.
     * @param new_value Value to assign to *it when p(*it) returns true.
     */
    template<class ForwardIt, class UnaryPredicate, class T>
    constexpr void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p, T const& new_value)
    {
        while(not(first == last))
        {
            if(static_cast<bool>(p(*first))) *first = new_value;
            ++first;
        }
    };

    /**
     * Replace all instances of old_value in range [first, last) with new_value.
     */
    template<class ForwardIt, class T>
    constexpr void replace(ForwardIt first, ForwardIt last, T const& old_value, T const& new_value)
    {
        return replace_if(first, last, [&old_value](auto const& v){return v == old_value;}, new_value);
    };


    /**
     * Copy elements from a range into a new range, replacing certain elements with a new value.
     * @tparam InputIt Input iterator type
     * @tparam OutputIt Output iterator type.
     * @tparam UnaryPredicate Predicate type
     * @tparam T New value type. Must be assignable to *d_first.
     * @param first Start of source range.
     * @param last End of source range.
     * @param d_first Start of destination range
     * @param p Predicate. If p(*it) returns false, then *it is copied. Otherwise, if p(*it) returns true, then new_value
     * is copied instead
     * @param new_value New value to be used when p(*it) returns true. Must be assignable to *d_first.
     * @return Iterator to the end of the destination range.
     */
    template<class InputIt, class OutputIt, class UnaryPredicate, class T>
    constexpr OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p, T const& new_value)
    {
        static_assert(is_input_iterator<InputIt>::value, "first must be input iterator");
        while(not(first == last))
        {
            if(p(*first)) *d_first = new_value;
            else *d_first = *first;
            ++d_first;
            ++first;
        }
        return d_first;
    };


    /**
     * Copy elements from a range into a new range, replacing certain elements with a new value.
     * @tparam InputIt Input iterator type
     * @tparam OutputIt Output iterator type.
     * @tparam T New value type. Must be assignable to *d_first.
     * @param first Start of source range.
     * @param last End of source range.
     * @param d_first Start of destination range
     * @param old_value Value that will be replaced in the new range. Any values in the source range comaring equal to
     * this value will be replaced with new_value.
     * @param new_value New value to be used when (*it == old_value) returns true. Must be assignable to *d_first.
     * @return Iterator to the end of the destination range.
     */
    template<class InputIt, class OutputIt, class T>
    constexpr OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first, T const& old_value, T const& new_value)
    {
        return replace_copy_if(first, last, d_first, [&old_value](auto const& v){return v == old_value;}, new_value);
    };

    /**
     * Swap the two ranges. Calls std::swap on each corresponding element in [first1, last1) and [first2, first2+ distance(last1, first1) )
     * @tparam ForwardIt1 First range iterator type
     * @tparam ForwardIt2  Second range iterator type
     * @param first1  Start of first range
     * @param last1  End of first range
     * @param first2  Start of second range
     * @return  End of second range.
     */
    template<class ForwardIt1, class ForwardIt2>
    constexpr ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2 )
    {
        static_assert(is_forward_iterator<ForwardIt1>::value, "first1 must be forward iterator");
        static_assert(is_forward_iterator<ForwardIt2>::value, "first2 must be forward iterator");
        while(not(first1 == last1))
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
        if(not(a==b)) swap(*a, *b);
    };

    template<class BidirIt>
    constexpr void reverse(BidirIt first, BidirIt last)
    {
        static_assert(is_bidirectional_iterator<BidirIt>::value, "first must be a bidirectional iterator");
        while(not(first == last) and not(first == --last))
        {
            iter_swap(first, last);
            ++first;
        }
    }

    template<class BidirIt, class OutputIt>
    constexpr OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first)
    {
        static_assert(is_bidirectional_iterator<BidirIt>::value, "first must be a bidirectional iterator");
        while(not(first == last))
        {
            *d_first = *(--last);
            ++d_first;
        }
        return d_first;
    };

    //rotate n_first left to first.
    /**
     * Left-rotate the range [first, last) such that the element at n_first becomes first, and n_first-1 becomes last.
     * @tparam ForwardIt Iterator type
     * @param first Start of range.
     * @param n_first Element that will be rotated to the first position in the range.
     * @param last End of the range.
     * @return the iterator equal to first+(last-n_first); (ie. the new position of  the value that was at first)
     */
    template<class ForwardIt>
    constexpr ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        if(first == n_first) return first;
        if(n_first == last) return last;

        ForwardIt next = n_first;

        do
        {
            iter_swap(first, next);
            ++first;
            ++next;
            if(first == n_first) n_first = next;
        }
        while(not(next == last));

        ForwardIt ret = first;
        for(next = n_first; not(next == last); )
        {
            iter_swap(first, next);
            ++first;
            ++next;
            if(first == n_first) n_first = next;
            else if(next == last) next = n_first;
        }
        return ret;
    }

    /**
     * Copies the elements in [first, last) to another range beginning with d_first, such
     * that the element in position n_first in the source range is in the first position
     * in the destination range, and the first element in the source range and the element
     * at (n_first-1) becomes the last element in the output range.
     * @tparam ForwardIt Source iterator type
     * @tparam OutputIt Destination iterator type
     * @param first First element of the source range
     * @param n_first  element of the source range that will be first in the destination range.
     * @param last End of the source range
     * @param d_first Start of the destination range.
     * @return End of the destination range.
     */
    template<class ForwardIt, class OutputIt>
    constexpr OutputIt rotate_copy(ForwardIt first, ForwardIt n_first, ForwardIt last, OutputIt d_first)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be a forward iterator");
        d_first = copy(n_first, last, d_first);
        return copy(first, n_first, d_first);
    };

    //unique: collapse consecutive equal values
    /**
     * Eliminates all but the first element from every consecutive group of equivalent elements
     * from the range [first, last) and returns a past-the-end iterator for the new logical
     * end fo the range.
     *
     * Removing is done by shifting the elements in the range in such a way thtat elements to
     * be erased are overwritten. Relative order of the elements that remain is preserved and the
     * physical size of the container is unchanged. Iterators pointing to an element between the new
     * new logical end and the physical end of the range are still dereferencable, but the elements
     * themselves have unspecified values.
     *
     * Typically, a call to unique is usually followed by a call to the container's erase method,
     * which erases the unspecified values and shrinks the container size.
     *
     * @tparam ForwardIt Forward iterator type
     * @tparam BinaryPredicate Binary predicate type
     * @param first Start of the range.
     * @param last End of the range
     * @param p A binary predicate used to determine equality. Should return a result coercible to bool.
     * @return An end iterator for the result range.
     */
    template<class ForwardIt, class BinaryPredicate>
    constexpr ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "first must be forward iterator");
        //find the first set of consecutve elements.
        auto last_insert = ajacent_find(first, last, p);
        if(last_insert == last) return last; //found no duplicates.
        //look forward until we find something not equal to last_insert
        first = last_insert + 1;
        while(not(first == last))
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

    /**
     * Eliminates all but the first element from every consecutive group of equivalent elements
     * from the range [first, last) and returns a past-the-end iterator for the new logical
     * end fo the range. The elements are compared using operator==
     *
     * Removing is done by shifting the elements in the range in such a way thtat elements to
     * be erased are overwritten. Relative order of the elements that remain is preserved and the
     * physical size of the container is unchanged. Iterators pointing to an element between the new
     * new logical end and the physical end of the range are still dereferencable, but the elements
     * themselves have unspecified values.
     *
     * Typically, a call to unique is usually followed by a call to the container's erase method,
     * which erases the unspecified values and shrinks the container size.
     *
     * @tparam ForwardIt Forward iterator type
     * @param first Start of the range.
     * @param last End of the range
     * @return An end iterator for the result range.
     */
    template<class ForwardIt>
    constexpr ForwardIt unique(ForwardIt first, ForwardIt last)
    {
        return unique(first, last, detail::equal());
    }

    template<class InputIt, class OutputIt, class BinaryPredicate>
    constexpr InputIt unique_copy(InputIt first, InputIt last, OutputIt d_first, BinaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, " InputIt must be input iterator");
        auto last_unique= first;
        *d_first = *first;
        ++first;
        ++d_first;
        while(not(first == last))
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
    template<class InputIt, class OutputIt>
    constexpr InputIt unique_copy(InputIt first, InputIt last, OutputIt d_first)
    {
        return unique_copy(first, last, d_first, detail::equal());
    };

    /**
     * Returns true if all elements in the range [first, last) that satisfy the predicate p appear before
     * all elements that do not. Also returns true on an empty range.
     * @tparam InputIt Input iterator type
     * @tparam UnaryPredicate Unary predicate type.
     * @param first Start of range
     * @param last End of range
     * @param p Partition predicate.
     * @return True if all elements for which p(e) == true appear before elements for which p(e) == false. Otherwise,
     * returns false.
     */
    template<class InputIt, class UnaryPredicate>
    constexpr bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p)
    {
        static_assert(is_input_iterator<InputIt>::value, " InputIt must be input iterator");
        static_assert(detail::is_unary_predicate_v<UnaryPredicate, InputIt>, "p must be callable with iterator value type");
        if(first == last) return true;
        bool reached_partition = false; //set to true on the first false result.
        while(not(first == last))
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
        static_assert(detail::is_unary_predicate_v<UnaryPredicate, ForwardIt>, "p must be a unary predicate on ForwardIt");

        //advance first to first false item.
        first = find_if_not(first, last, p);
        if(first == last) return first; //no false items, so nothing to do here.

        for(auto i = next(first); not(i == last); ++i)
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
        OutputIt2 d_first_false,
        UnaryPredicate p
    )
    {
        static_assert(is_input_iterator<InputIt>::value, " InputIt must be input iterator");
        while(not(first == last))
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
        while(not(i == last))
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
                while(not(first == last))
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

                while(not(first == last))
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

    template<class ForwardIt, class Compare>
    constexpr ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp)
    {
        static_assert(is_forward_iterator<ForwardIt>::value, "Iterator must be a forward iterator");

        auto i = next(first);

        while(not(i == last))
        {
            if(not comp(*first,  *i)) return i;
            ++first;
            ++i;
        }
        return i;
    };
    template<class ForwardIt>
    constexpr ForwardIt is_sorted_until(ForwardIt first, ForwardIt last)
    {
        return is_sorted_until(first, last, detail::less());
    }

    template<class ForwardIt, class Compare>
    constexpr bool is_sorted(ForwardIt first, ForwardIt last, Compare comp)
    {
        return is_sorted_until(first, last, comp) == last;
    };
    template<class ForwardIt>
    constexpr bool is_sorted(ForwardIt first, ForwardIt last)
    {
        return is_sorted_until(first, last) == last;
    }

    //standard quicksort.
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
    template<class RandomIt>
    void sort(RandomIt first, RandomIt last)
    {
        return sort(first, last, detail::less());
    }

    //check for max heap.
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
    RandomIt is_heap_until(RandomIt first, RandomIt last)
    {
        return is_heap_until(first, last, detail::less());
    }


    template<class RandomIt, class Compare>
    bool is_heap(RandomIt first, RandomIt last, Compare comp)
    {
        return is_heap_until(first, last, comp) == last;
    };
    template<class RandomIt>
    bool is_heap(RandomIt first, RandomIt last)
    {
        return is_heap_until(first, last, detail::less());
    };

    //element last-1 is the element to insert.
    template<class RandomIt, class Compare>
    void push_heap(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        if(first == last) return;
        if(next(first) == last) return;
        auto elem = last-1;
        while(not(elem == first))
        {
            const auto parent = first + (distance(first, elem) - 1)/2; not(parent == first);
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
    void push_heap(RandomIt first, RandomIt last)
    {
        push_heap(first, last, detail::less());
    }

    template<class RandomIt, class Compare>
    void make_heap(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");

        auto heap_end = first + 1; //start with one-element heap.

        while(not(heap_end == last))
        {
            ++heap_end;  //add next element onto bottom of heap.
            push_heap(first, heap_end, comp);
        }
    };
    template<class RandomIt>
    void make_heap(RandomIt first, RandomIt last)
    {
        make_heap(first, last, detail::less());
    }


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
                if(not(right_child == last))
                {
                    if(comp(*elem, *right_child) and comp(*left_child, *right_child)) swap_location = right_child;
                }
                if(not(swap_location == elem))
                {
                    iter_swap(elem, swap_location);
                    elem = swap_location;
                    continue;
                }
            }
        };
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
    void pop_heap(RandomIt first, RandomIt last)
    {
        pop_heap(first, last, detail::less());
    }

    template<class RandomIt, class Compare>
    void sort_heap(RandomIt first, RandomIt last, Compare comp)
    {
        static_assert(is_random_access_iterator<RandomIt>::value, "Iterators must be random access");
        while(not(first == last))
        {
            pop_heap(first, last, comp);
            --last;
        }
    };
    template<class RandomIt>
    void sort_heap(RandomIt first, RandomIt last)
    {
        return sort_heap(first, last, detail::less());
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
    template<class RandomIt>
    void partial_sort(RandomIt first, RandomIt middle, RandomIt last)
    {
        return partial_sort(first, middle, last, detail::less());
    }

    //heapsort here.
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
        while(not(first == last) and not(heap_end == d_last))
        {
            *heap_end = *first;
            ++first;
            ++heap_end;
        }
        make_heap(d_first, heap_end);
        //result is now a maximal heap. So if we replace the top(front) element and percolate, then
        //eventually the largest elements will be removed.
        while(not(first == last))
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
    template<class InputIt, class RandomIt>
    RandomIt partial_sort_copy(InputIt first, InputIt last, RandomIt d_first, RandomIt d_last)
    {
        return partial_sort_copy(first, last, d_first, d_last, detail::less());
    };

    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        static_assert(is_input_iterator<InputIt1>::value, "InputIt1 must be an input iterator");
        static_assert(is_input_iterator<InputIt2>::value, "InputIt2 must be an input iterator");

        while(not(first1 == last1) and not(first2 == last2))
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
        if(not(first1 == last1))
        {
            d_first = copy(first1, last1, d_first);
        }
        else if(not(first2 == last2))
        {
            d_first = copy(first2, last2, d_first);
        }
        return d_first;
    };

    template<class InputIt1, class InputIt2, class OutputIt>
    OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return merge(first1, last1, first2, last2, d_first, detail::less());
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
        return inplace_merge(first, midpoint, last, detail::less());
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
        return stable_sort(first, last, detail::less());
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
        while(not(ip == prev(last)))
        {
            auto best = ip+1;
            first = best;
            while(not(first == last))
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
        return nth_element(first, nth, last, detail::less());
    }

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
    ForwardIt lower_bound(ForwardIt first, ForwardIt last, T  const& val)
    {
        return lower_bound(first, last, val, detail::less());
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
    ForwardIt upper_bound(ForwardIt first, ForwardIt last, T  const& val)
    {
        return upper_bound(first, last, val, detail::less());
    };


    template<class ForwardIt, class T, class Compare>
    bool binary_search(ForwardIt first, ForwardIt last, T const& value, Compare comp)
    {
        first = lower_bound(first, last, value, comp);
        return (not(first == last) and not comp(value, *first));
    };
    template<class ForwardIt, class T>
    bool binary_search(ForwardIt first, ForwardIt last, T const& value)
    {
        return binary_search(first, last, value, detail::less());
    };

    template<class ForwardIt, class T, class Compare>
    pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last, T const& value, Compare comp)
    {
        return {lower_bound(first, last, value, comp), upper_bound(first, last, value, comp)};
    };
    template<class ForwardIt, class T>
    pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last, T const& value)
    {
        return equal_range(first, last, value, detail::less());
    };

    template<class InputIt1, class InputIt2, class Compare>
    constexpr bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        static_assert(is_input_iterator<InputIt1>::value, "first1 and last1 must be input iterators");
        static_assert(is_input_iterator<InputIt2>::value, "first2 and last2 must be input iterators");
        for(;not(first2 == last2); ++first1)
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
        return includes(first1, last1, first2, last2, detail::less());
    };

    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while(not(first1 == last1))
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
        return set_difference(first1, last1, first2, last2, d_first, detail::less());
    };
    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while(not(first1 == last1) and not(first2 == last2))
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
        return set_intersection(first1, last1, first2, last2, d_first, detail::less());
    };
    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while(not(first1 == last1))
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
        return set_symmetric_difference(first1, last1, first2, last2, d_first, detail::less());
    };
    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        for(; not(first1 == last1); ++d_first)
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
        return set_union(first1, last1, first2, last2, d_first, detail::less());
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
        if(first == last) return first;
        auto ret = first;
        ++first;
        while(not(first == last))
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
        return max_element(first, last, detail::less());
    }
    template<class ForwardIt, class Compare>
    constexpr ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)
    {
        if(first == last) return first;
        auto ret = first;
        ++first;
        while(not(first == last))
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
        return min_element(first, last, detail::less());
    }

    template<class ForwardIt, class Compare>
    constexpr pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last, Compare comp)
    {
        if(first == last) return {first, first};
        pair<ForwardIt, ForwardIt> ret = {first, first};
        ++first;
        while(not(first == last))
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
        return minmax_element(first, last, detail::less());
    };
    template<class InputIt1, class InputIt2, class Compare>
    bool lexographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        while(not(first1 == last1) and not(first2 == last2))
        {
            if(comp(*first1, *first2)) return true;
            else if(comp(*first2, *first1)) return false;
            ++first1;
            ++first2;
        }
        //at least one of the ranges has ended.
        return (first1 == last1 and not(first2 == last2));
    };
    template<class InputIt1, class InputIt2>
    bool lexographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        return lexographical_compare(first1, last1, first2, last2, detail::less());
    };
    //todo: permutations.
};




