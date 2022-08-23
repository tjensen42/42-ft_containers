#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "vector.hpp"

namespace ft
{
template <typename T, typename Container = ft::vector<T> >
class stack
{
   public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

   protected:
    container_type c;

   public:
    explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {}
    explicit stack(const stack& other) : c(other.c) {}

    ~stack() {}

    stack& operator=(const stack& other)
    {
        c = other.c;
        return *this;
    }

    bool empty() const { return c.empty(); }

    size_type size() const { return c.size(); }

    reference top() { return c.back(); }

    const_reference top() const { return c.back(); }

    void push(const value_type& x) { c.push_back(x); }

    void pop() { c.pop_back(); }

    template <typename T1, typename C1>
    friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

    template <typename T1, typename C1>
    friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
};

template <typename T, typename Container>
inline bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return lhs.c == rhs.c;
}

template <typename T, typename Container>
inline bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Container>
inline bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return lhs.c < rhs.c;
}

template <typename T, typename Container>
inline bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Container>
inline bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Container>
inline bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(lhs < rhs);
}

}  // namespace ft

#endif  // FT_STACK_HPP
