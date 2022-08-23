#ifndef FT_ITERATOR_TRAITS_HPP
#define FT_ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iterator>

#include "type_traits.hpp"

namespace ft
{
/*
** iterator_traits
*/
// struct input_iterator_tag
// {};

// struct output_iterator_tag
// {};

// struct forward_iterator_tag
//     : public input_iterator_tag
// {};

// struct bidirectional_iterator_tag
//     : public forward_iterator_tag
// {};

// struct random_access_iterator_tag
//     : public bidirectional_iterator_tag
// {};

typedef std::output_iterator_tag        output_iterator_tag;
typedef std::input_iterator_tag         input_iterator_tag;
typedef std::forward_iterator_tag       forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*,
          typename Reference = T&>
struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template <typename Iter>
struct iterator_traits {
    typedef typename Iter::value_type        value_type;
    typedef typename Iter::difference_type   difference_type;
    typedef typename Iter::pointer           pointer;
    typedef typename Iter::reference         reference;
    typedef typename Iter::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T*> {
    typedef T                          value_type;
    typedef std::ptrdiff_t             difference_type;
    typedef T*                         pointer;
    typedef T&                         reference;
    typedef random_access_iterator_tag iterator_category;
};

template <typename T>
struct iterator_traits<const T*> {
    typedef T                          value_type;
    typedef std::ptrdiff_t             difference_type;
    typedef const T*                   pointer;
    typedef const T&                   reference;
    typedef random_access_iterator_tag iterator_category;
};

/*
**  iter_helper
*/
template <typename Iter>
inline typename iterator_traits<Iter>::iterator_category iterator_category(const Iter&)
{
    return typename iterator_traits<Iter>::iterator_category();
}

/*
** normal_iterator
*/
template <typename Iter, typename Container>
class normal_iterator
{
   protected:
    Iter current_;

    typedef ft::iterator_traits<Iter> traits_type_;

   public:
    typedef Iter                                     iterator_type;
    typedef typename traits_type_::iterator_category iterator_category;
    typedef typename traits_type_::value_type        value_type;
    typedef typename traits_type_::difference_type   difference_type;
    typedef typename traits_type_::pointer           pointer;
    typedef typename traits_type_::reference         reference;

    normal_iterator() : current_(iterator_type()) {}

    normal_iterator(const iterator_type& other) : current_(other) {}

    template <typename U>
    normal_iterator(const normal_iterator<
                    U, typename ft::enable_if<ft::are_same<U, typename Container::pointer>::value,
                                              Container>::type>& it)
        : current_(it.base())
    {
    }

    ~normal_iterator() {}

    reference operator*() const { return *current_; }

    reference operator[](difference_type n) const { return current_[n]; }

    pointer operator->() const { return &(operator*()); }

    normal_iterator& operator++()
    {
        ++current_;
        return *this;
    }

    normal_iterator operator++(int)
    {
        normal_iterator tmp(*this);
        ++current_;
        return tmp;
    }

    normal_iterator& operator--()
    {
        --current_;
        return *this;
    }

    normal_iterator operator--(int)
    {
        normal_iterator tmp(*this);
        --current_;
        return tmp;
    }

    normal_iterator operator+(difference_type n) const { return normal_iterator(current_ + n); }

    normal_iterator& operator+=(difference_type n)
    {
        current_ += n;
        return *this;
    }

    normal_iterator operator-(difference_type n) const { return normal_iterator(current_ - n); }

    normal_iterator& operator-=(difference_type n)
    {
        current_ -= n;
        return *this;
    }

    iterator_type base() const { return current_; }
};

template <typename IterL, typename IterR, typename Container>
inline bool operator==(const normal_iterator<IterL, Container>& lhs,
                       const normal_iterator<IterR, Container>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename IterL, typename IterR, typename Container>
inline bool operator!=(const normal_iterator<IterL, Container>& lhs,
                       const normal_iterator<IterR, Container>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename IterL, typename IterR, typename Container>
inline bool operator<(const normal_iterator<IterL, Container>& lhs,
                      const normal_iterator<IterR, Container>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename IterL, typename IterR, typename Container>
inline bool operator<=(const normal_iterator<IterL, Container>& lhs,
                       const normal_iterator<IterR, Container>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename IterL, typename IterR, typename Container>
inline bool operator>(const normal_iterator<IterL, Container>& lhs,
                      const normal_iterator<IterR, Container>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename IterL, typename IterR, typename Container>
inline bool operator>=(const normal_iterator<IterL, Container>& lhs,
                       const normal_iterator<IterR, Container>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename IterL, typename IterR, typename Container>
inline typename normal_iterator<IterL, Container>::difference_type operator-(
    const normal_iterator<IterL, Container>& lhs, const normal_iterator<IterR, Container>& rhs)
{
    return lhs.base() - rhs.base();
}

template <typename Iter, typename Container>
inline typename normal_iterator<Iter, Container>::difference_type operator-(
    const normal_iterator<Iter, Container>& lhs, const normal_iterator<Iter, Container>& rhs)
{
    return lhs.base() - rhs.base();
}

template <typename Iter, typename Container>
inline normal_iterator<Iter, Container> operator+(
    typename normal_iterator<Iter, Container>::difference_type n,
    normal_iterator<Iter, Container>                           it)
{
    it += n;
    return it;
}

/*
** reverse_iterator
*/
template <typename Iter>
class reverse_iterator : public iterator<typename ft::iterator_traits<Iter>::iterator_category,
                                         typename ft::iterator_traits<Iter>::value_type,
                                         typename ft::iterator_traits<Iter>::difference_type,
                                         typename ft::iterator_traits<Iter>::pointer,
                                         typename ft::iterator_traits<Iter>::reference>
{
   protected:
    Iter current_;

    typedef ft::iterator_traits<Iter> traits_type_;

   public:
    typedef Iter                                     iterator_type;
    typedef typename traits_type_::iterator_category iterator_category;
    typedef typename traits_type_::value_type        value_type;
    typedef typename traits_type_::difference_type   difference_type;
    typedef typename traits_type_::pointer           pointer;
    typedef typename traits_type_::reference         reference;

    reverse_iterator() : current_() {}

    explicit reverse_iterator(iterator_type x) : current_(x) {}

    template <typename U>
    reverse_iterator(const reverse_iterator<U>& x) : current_(x.base())
    {
    }

    ~reverse_iterator() {}

    template <typename U>
    reverse_iterator& operator=(const reverse_iterator<U>& other)
    {
        current_ = other.base();
        return *this;
    }

    iterator_type base() const { return current_; }

    reference operator*() const
    {
        iterator_type tmp = current_;
        return *(--tmp);
    }

    pointer operator->() const { return &(operator*()); }

    reverse_iterator& operator++()
    {
        --current_;
        return *this;
    }

    reverse_iterator operator++(int)
    {
        reverse_iterator tmp(*this);
        --current_;
        return tmp;
    }

    reverse_iterator& operator--()
    {
        ++current_;
        return *this;
    }

    reverse_iterator operator--(int)
    {
        reverse_iterator tmp(*this);
        ++current_;
        return tmp;
    }

    reverse_iterator operator+(difference_type n) const { return reverse_iterator(current_ - n); }

    reverse_iterator& operator+=(difference_type n)
    {
        current_ -= n;
        return *this;
    }

    reverse_iterator operator-(difference_type n) const { return reverse_iterator(current_ + n); }

    reverse_iterator& operator-=(difference_type n)
    {
        current_ += n;
        return *this;
    }

    reference operator[](difference_type n) const { return *(*this + n); }
};

template <typename IterL, typename IterR>
inline bool operator==(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename IterL, typename IterR>
inline bool operator!=(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename IterL, typename IterR>
inline bool operator<(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename IterL, typename IterR>
inline bool operator<=(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename IterL, typename IterR>
inline bool operator>(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename IterL, typename IterR>
inline bool operator>=(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename Iter>
inline typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs,
                                                                  const reverse_iterator<Iter>& rhs)
{
    return rhs.base() - lhs.base();
}

template <typename IterL, typename IterR>
inline typename reverse_iterator<IterL>::difference_type operator-(
    const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
{
    return rhs.base() - lhs.base();
}

template <typename Iter>
inline reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
                                        const reverse_iterator<Iter>&                    rit)
{
    return reverse_iterator<Iter>(rit.base() - n);
}

/*
**  distance
*/
template <typename InputIter>
inline typename ft::iterator_traits<InputIter>::difference_type _distance(InputIter first,
                                                                          InputIter last,
                                                                          input_iterator_tag)
{
    typename ft::iterator_traits<InputIter>::difference_type count(0);
    while (first != last) {
        ++first;
        ++count;
    }
    return count;
}

template <typename RandomAccessIter>
inline typename ft::iterator_traits<RandomAccessIter>::difference_type _distance(
    RandomAccessIter first, RandomAccessIter last, random_access_iterator_tag)
{
    return last - first;
}

template <typename InputIter>
inline typename ft::iterator_traits<InputIter>::difference_type distance(InputIter first,
                                                                         InputIter last)
{
    return _distance(first, last, typename ft::iterator_traits<InputIter>::iterator_category());
}

template <typename InputIter>
inline InputIter next(InputIter iter)
{
    return ++iter;
}

}  // namespace ft

#endif  // FT_ITERATOR_TRAITS_H
