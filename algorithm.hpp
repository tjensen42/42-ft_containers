#ifndef FT_ALGORITHM_HPP
#define FT_ALGORITHM_HPP

namespace ft
{
/*
**  equal
*/
template <typename InputIterator1, typename InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    while (first1 != last1) {
        if (!(*first1 == *first2)) return false;
        ++first1;
        ++first2;
    }
    return true;
}

template <typename InputIterator1, typename InputIterator2,
          typename BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
           BinaryPredicate pred)
{
    while (first1 != last1) {
        if (!pred(*first1, *first2)) return false;
        ++first1;
        ++first2;
    }
    return true;
}

/*
**  lexicographical_compare
*/
template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2)
{
    while ((first1 != last1) && (first2 != last2)) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
        ++first1;
        ++first2;
    }
    return (first1 == last1) && (first2 != last2);
}

template <typename InputIterator1, typename InputIterator2, typename Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2,
                             Compare comp)
{
    while ((first1 != last1) && (first2 != last2)) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
        ++first1;
        ++first2;
    }
    return (first1 == last1) && (first2 != last2);
}

/*
**  Helpers
*/
template <typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
const T& max(const T& a, const T& b)
{
    return a > b ? a : b;
}

template <typename T>
const T& min(const T& a, const T& b)
{
    return a < b ? a : b;
}

template <typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T& val)
{
    while (first != last) {
        *first = val;
        ++first;
    }
}

template <typename OutputIterator, typename Size, typename T>
void fill_n(OutputIterator first, Size n, const T& val)
{
    while (n > 0) {
        *first = val;
        ++first;
        --n;
    }
}

template <typename InputIterator, typename OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
                    OutputIterator result)
{
    while (first != last) {
        *result = *first;
        ++result;
        ++first;
    }
    return result;
}

template <typename BidirIterator1, typename BidirIterator2>
BidirIterator2 copy_backward(BidirIterator1 first, BidirIterator1 last,
                             BidirIterator2 result_last)
{
    while (last != first) {
        --last;
        --result_last;
        *result_last = *last;
    }
    return result_last;
}

}  // namespace ft

#endif  // FT_ALGORITHM_HPP
