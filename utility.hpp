#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

namespace ft
{
/*
** pair
*/
template <class T1, class T2>
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair() : first(T1()), second(T2()) {}

    template <class U, class V>
    pair(const pair<U, V>& pr) : first(pr.first), second(pr.second)
    {
    }

    pair(const T1& a, const T2& b) : first(a), second(b) {}

    ~pair() {}

    pair& operator=(const pair& pr)
    {
        first = pr.first;
        second = pr.second;
        return *this;
    }
};

template <class T1, class T2>
inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return x.first == y.first && x.second == y.second;
}

template <class T1, class T2>
inline bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return !(x == y);
}

template <class T1, class T2>
inline bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}

template <class T1, class T2>
inline bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return !(y < x);
}

template <class T1, class T2>
inline bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return y < x;
}

template <class T1, class T2>
inline bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return !(x < y);
}

/*
** make_pair
*/
template <typename T1, typename T2>
inline pair<T1, T2> make_pair(T1 x, T2 y)
{
    return ft::pair<T1, T2>(x, y);
}

}  // namespace ft

#endif  // FT_UTILITY_HPP
