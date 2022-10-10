#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <exception>
#include <memory>
#include <limits>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{
    template <typename T, typename Allocator = std::allocator<T>>
    class vector
    {
    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::normal_iterator<pointer, vector> iterator;
        typedef ft::normal_iterator<const_pointer, vector> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        explicit vector(const allocator_type &alloc = allocator_type())
            : alloc_(alloc), begin_(nullptr), end_(nullptr), end_cap_(nullptr)
        {
        }

        explicit vector(size_type n)
            : begin_(nullptr), end_(nullptr), end_cap_(nullptr)
        {
            try
            {
                if (n > 0)
                {
                    vallocate_(n);
                    construct_from_end_(n);
                }
            }
            catch (...)
            {
                vdeallocate_();
                throw;
            }
        }

        explicit vector(size_type n, const value_type &val,
                        const allocator_type &alloc = allocator_type())
            : alloc_(alloc), begin_(nullptr), end_(nullptr), end_cap_(nullptr)
        {
            try
            {
                if (n > 0)
                {
                    vallocate_(n);
                    construct_from_end_(n, val);
                }
            }
            catch (...)
            {
                vdeallocate_();
                throw;
            }
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
            : alloc_(alloc), begin_(nullptr), end_(nullptr), end_cap_(nullptr)
        {
            try
            {
                assign(first, last);
            }
            catch (...)
            {
                vdeallocate_();
                throw;
            }
        }

        vector(const vector &x)
            : alloc_(x.get_allocator()), begin_(nullptr), end_(nullptr), end_cap_(nullptr)
        {
            try
            {
                size_type n = x.size();
                if (n > 0)
                {
                    vallocate_(n);
                    construct_from_end_(x.begin_, x.end_, ft::iterator_category(x.begin_));
                }
            }
            catch (...)
            {
                vdeallocate_();
                throw;
            }
        }

        ~vector() { vdeallocate_(); }

        vector &operator=(const vector &other)
        {
            if (this != &other)
            {
                alloc_ = other.get_allocator();
                assign(other.begin(), other.end());
            }
            return *this;
        }

        allocator_type get_allocator() const { return alloc_; }

        reference at(size_type pos)
        {
            if (pos >= size())
                throw std::out_of_range("vector");
            return (*this)[pos];
        }

        const_reference at(size_type pos) const
        {
            if (pos >= size())
                throw std::out_of_range("vector");
            return (*this)[pos];
        }

        reference operator[](size_type index) { return begin_[index]; }

        const_reference operator[](size_type index) const { return begin_[index]; }

        reference front() { return *begin_; }

        const_reference front() const { return *begin_; }

        reference back() { return *(end_ - 1); }

        const_reference back() const { return *(end_ - 1); }

        iterator begin() { return iterator(begin_); }

        const_iterator begin() const { return const_iterator(begin_); }

        iterator end() { return iterator(end_); }

        const_iterator end() const { return const_iterator(end_); }

        reverse_iterator rbegin() { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

        reverse_iterator rend() { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        bool empty() const { return begin_ == end_; }

        size_type size() const { return static_cast<size_type>(end_ - begin_); }

        size_type max_size() const
        {
            return ft::min<size_type>(alloc_.max_size(), std::numeric_limits<difference_type>::max());
        }

        size_type capacity() const { return static_cast<size_type>(end_cap_ - begin_); }

        void clear() { destroy_from_end_(begin_); }

        void assign(size_type n, const value_type &val)
        {
            if (n <= capacity())
            {
                const size_type s = size();
                ft::fill_n(begin_, ft::min(n, s), val);
                if (n > s)
                    construct_from_end_(n - s, val);
                else
                    destroy_from_end_(begin_ + n);
            }
            else
            {
                vector tmp(n, val);
                swap(tmp);
            }
        }

        template <class InputIterator>
        void assign(
            InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
        {
            assign_range_(first, last, ft::iterator_category(first));
        }

        iterator insert(iterator position, const value_type &val)
        {
            difference_type offset = position - begin();
            insert(position, 1, val);
            return begin() + offset;
        }

        void insert(iterator position, size_type n, const value_type &val)
        {
            if (n > 0)
            {
                const difference_type offset = position - begin();
                const size_type old_size = size();
                reserve(recommend_size_(old_size + n));
                resize(old_size + n);
                ft::copy_backward(begin_ + offset, begin_ + old_size, begin_ + old_size + n);
                ft::fill_n(begin_ + offset, n, val);
            }
        }

        template <class InputIterator>
        void insert(
            iterator position, InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
        {
            insert_range_(position, first, last, ft::iterator_category(first));
        }

        iterator erase(iterator position)
        {
            if (position + 1 != end())
                ft::copy(position + 1, end(), position);
            pop_back();
            return position;
        }

        iterator erase(iterator first, iterator last)
        {
            if (first != last)
            {
                pointer p = begin_ + (first - begin());
                destroy_from_end_(ft::copy(p + (last - first), end_, p));
            }
            return first;
        }

        void push_back(const value_type &value)
        {
            if (end_ == end_cap_)
                reserve(recommend_size_(capacity() + 1));
            construct_from_end_(1, value);
        }

        void pop_back() { destroy_from_end_(end_ - 1); }

        void reserve(size_type n)
        {
            if (n > capacity())
            {
                vector tmp(alloc_);
                tmp.vallocate_(n);
                tmp.construct_from_end_(begin_, end_, ft::iterator_category(begin_));
                swap(tmp);
            }
        }

        void resize(size_type n, value_type val = value_type())
        {
            const size_type current_size = size();
            if (current_size < n)
            {
                reserve(recommend_size_(n));
                construct_from_end_(n - current_size, val);
            }
            else if (current_size > n)
                destroy_from_end_(begin_ + n);
        }

        void swap(vector &x)
        {
            ft::swap(alloc_, x.alloc_);
            ft::swap(begin_, x.begin_);
            ft::swap(end_, x.end_);
            ft::swap(end_cap_, x.end_cap_);
        }

    private:
        allocator_type alloc_;
        pointer begin_;
        pointer end_;
        pointer end_cap_;

        inline void construct_(pointer p) { alloc_.construct(p); }
        inline void construct_(pointer p, const_reference val) { alloc_.construct(p, val); }

        inline void destroy_(pointer p) { alloc_.destroy(p); }

        inline void vallocate_(size_type n)
        {
            if (n > max_size())
                throw std::length_error("vector");
            begin_ = end_ = alloc_.allocate(n);
            end_cap_ = begin_ + n;
        }

        inline void vdeallocate_()
        {
            if (begin_ != nullptr)
            {
                clear();
                alloc_.deallocate(begin_, capacity());
                begin_ = end_ = end_cap_ = nullptr;
            }
        }

        inline void construct_from_end_(size_type n)
        {
            for (size_type i = 0; i < n; ++i, ++end_)
                construct_(end_);
        }

        inline void construct_from_end_(size_type n, const_reference val)
        {
            for (size_type i = 0; i < n; ++i, ++end_)
                construct_(end_, val);
        }

        template <typename ForwardIterator>
        inline void construct_from_end_(ForwardIterator first, ForwardIterator last,
                                        ft::forward_iterator_tag)
        {
            for (; first != last; ++first, ++end_)
                construct_(end_, *first);
        }

        inline void destroy_from_end_(pointer new_end)
        {
            while (end_ != new_end)
                destroy_(--end_);
        }

        template <typename InputIterator>
        inline void assign_range_(InputIterator first, InputIterator last, ft::input_iterator_tag)
        {
            clear();
            for (; first != last; ++first)
                push_back(*first);
        }

        template <typename ForwardIterator>
        inline void assign_range_(ForwardIterator first, ForwardIterator last, ft::forward_iterator_tag)
        {
            clear();
            const size_type n = static_cast<size_type>(ft::distance(first, last));
            if (n > 0)
            {
                if (n > capacity())
                {
                    vdeallocate_();
                    vallocate_(n);
                }
                construct_from_end_(first, last, ft::iterator_category(first));
            }
        }

        template <typename InputIterator>
        void insert_range_(iterator pos, InputIterator first, InputIterator last,
                           ft::input_iterator_tag)
        {
            if (pos == end())
            {
                for (; first != last; ++first)
                    push_back(*first);
            }
            else if (first != last)
            {
                vector tmp(first, last);
                insert(pos, tmp.begin(), tmp.end());
            }
        }

        template <class ForwardIterator>
        void insert_range_(iterator position, ForwardIterator first, ForwardIterator last,
                           ft::forward_iterator_tag)
        {
            size_type n = static_cast<size_type>(ft::distance(first, last));
            if (n > 0)
            {
                const difference_type offset = position - begin();
                const size_type old_size = size();
                reserve(recommend_size_(old_size + n));
                resize(old_size + n);
                ft::copy_backward(begin_ + offset, begin_ + old_size, begin_ + old_size + n);
                ft::copy(first, last, begin_ + offset);
            }
        }

        inline size_type recommend_size_(size_type new_size) const
        {
            const size_type ms = max_size();
            if (new_size > ms)
                throw std::length_error("vector");
            const size_type cap = capacity();
            if (new_size <= cap)
                return new_size;
            if (cap >= ms / 2)
                return ms;
            return ft::max(2 * cap, new_size);
        }
    };

    template <typename T, typename Allocator>
    inline bool operator==(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename T, typename Allocator>
    inline bool operator!=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T, typename Allocator>
    inline bool operator<(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename T, typename Allocator>
    inline bool operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(rhs < lhs);
    }

    template <typename T, typename Allocator>
    inline bool operator>(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return rhs < lhs;
    }

    template <typename T, typename Allocator>
    inline bool operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(lhs < rhs);
    }

    template <typename T, typename Allocator>
    inline void swap(vector<T, Allocator> &x, vector<T, Allocator> &y)
    {
        x.swap(y);
    }

} // namespace ft

#endif // FT_VECTOR_HPP
