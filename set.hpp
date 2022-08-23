#ifndef FT_SET_HPP
#define FT_SET_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "red_black_tree.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{
template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T> >
class set
{
   public:
    typedef T                                        key_type;
    typedef key_type                                 value_type;
    typedef Compare                                  key_compare;
    typedef key_compare                              value_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

   private:
    typedef ft::RBTree<value_type, value_compare, allocator_type> tree_type;

   public:
    typedef typename tree_type::size_type              size_type;
    typedef typename tree_type::difference_type        difference_type;
    typedef typename tree_type::const_iterator         iterator;
    typedef typename tree_type::const_iterator         const_iterator;
    typedef typename tree_type::const_reverse_iterator reverse_iterator;
    typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

   public:
    explicit set(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : tree_(comp, alloc)
    {
    }

    template <class InputIterator>
    set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : tree_(comp, alloc)
    {
        tree_.insert_unique_range(first, last);
    }

    set(const set& x) : tree_(x.tree_) {}

    ~set() {}

    set& operator=(const set& x)
    {
        tree_ = x.tree_;
        return *this;
    }

    allocator_type get_allocator() const { return tree_.get_allocator(); }

    iterator begin() { return tree_.begin(); }

    const_iterator begin() const { return tree_.begin(); }

    iterator end() { return tree_.end(); }

    const_iterator end() const { return tree_.end(); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    bool empty() const { return tree_.size() == 0; }

    size_type size() const { return tree_.size(); }

    size_type max_size() const { return tree_.max_size(); }

    void clear() { return tree_.clear(); }

    ft::pair<iterator, bool> insert(const value_type& val) { return tree_.insert_unique(val); }

    iterator insert(iterator position, const value_type& val)
    {
        return tree_.insert_unique(position, val);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        return tree_.insert_unique_range(first, last);
    }

    void erase(iterator position) { tree_.erase_node(position); }

    size_type erase(const key_type& key) { return tree_.erase_unique(key); }

    void erase(iterator first, iterator last) { tree_.erase_range(first, last); }

    void swap(set& other) { tree_.swap(other.tree_); }

    size_type count(const key_type& key) const { return tree_.find(key) == end() ? 0 : 1; }

    iterator find(const key_type& key) const { return tree_.find(key); }

    ft::pair<iterator, iterator> equal_range(const key_type& key) const
    {
        return tree_.equal_range_unique(key);
    }

    iterator lower_bound(const key_type& key) const { return tree_.lower_bound(key); }

    iterator upper_bound(const key_type& key) const { return tree_.upper_bound(key); }

    key_compare key_comp() const { return key_compare(); }

    value_compare value_comp() const { return value_compare(key_comp()); }

   private:
    tree_type tree_;
};

template <typename T, typename Compare, typename Allocator>
inline bool operator==(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
{
    return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Compare, typename Allocator>
inline bool operator!=(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Compare, typename Allocator>
inline bool operator<(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Compare, typename Allocator>
inline bool operator<=(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Compare, typename Allocator>
inline bool operator>(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Compare, typename Allocator>
inline bool operator>=(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <typename T, typename Compare, typename Allocator>
inline void swap(set<T, Compare, Allocator>& x, set<T, Compare, Allocator>& y)
{
    x.swap(y);
}

}  // namespace ft

#endif  // FT_SET_HPP
