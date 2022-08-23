#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <exception>
#include <memory>

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
template <typename Key, typename T, typename Compare>
class map_value_type_compare : public std::binary_function<Key, Key, bool>
{
   public:
    typedef Key  first_argument_type;
    typedef Key  second_argument_type;
    typedef bool result_type;

   public:
    map_value_type_compare() : comp_() {}

    map_value_type_compare(const Compare& c) : comp_(c) {}

   public:
    const Compare& key_comp() const { return comp_; }

    bool operator()(const T& x, const T& y) const { return comp_(x.first, y.first); }

    bool operator()(const Key& x, const T& y) const { return comp_(x, y.first); }

    bool operator()(const T& x, const Key& y) const { return comp_(x.first, y); }

    void swap(map_value_type_compare& other) { std::swap(comp_, other.comp_); }

   protected:
    Compare comp_;
};

template <typename Key, typename T, typename Compare>
void swap(map_value_type_compare<Key, T, Compare>& x, map_value_type_compare<Key, T, Compare>& y)
{
    x.swap(y);
}

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
   public:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef ft::pair<const key_type, mapped_type>    value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

   private:
    typedef map_value_type_compare<key_type, value_type, key_compare>  value_type_compare;
    typedef ft::RBTree<value_type, value_type_compare, allocator_type> tree_type;

   public:
    typedef typename tree_type::iterator               iterator;
    typedef typename tree_type::const_iterator         const_iterator;
    typedef typename tree_type::reverse_iterator       reverse_iterator;
    typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

   public:
    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;

       protected:
        key_compare comp;
        value_compare(key_compare c) : comp(c) {}

       public:
        typedef bool       result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

        bool operator()(const value_type& x, const value_type& y) const
        {
            return comp(x.first, y.first);
        }
    };

   public:
    explicit map(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : tree_(value_type_compare(comp), alloc)
    {
    }

    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : tree_(value_type_compare(comp), alloc)
    {
        tree_.insert_unique_range(first, last);
    }

    map(const map& x) : tree_(x.tree_) {}

    ~map() {}

    map& operator=(const map& x)
    {
        tree_ = x.tree_;
        return *this;
    }

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

    key_compare key_comp() const { return key_compare(); }

    value_compare value_comp() const { return value_compare(key_comp()); }

    iterator find(const key_type& key) { return tree_.find(key); }

    const_iterator find(const key_type& key) const { return tree_.find(key); }

    size_type count(const key_type& key) const { return tree_.find(key) == end() ? 0 : 1; }

    mapped_type& operator[](const key_type& key)
    {
        return tree_.insert_unique(ft::make_pair(key, mapped_type())).first->second;
    }

    mapped_type& at(const key_type& key)
    {
        iterator it = find(key);
        if (it == end())
            throw std::out_of_range("map::at:  key not found");
        return it->second;
    }

    const mapped_type& at(const key_type& key) const
    {
        const_iterator it = find(key);
        if (it == end())
            throw std::out_of_range("map::at:  key not found");
        return it->second;
    }

    iterator lower_bound(const key_type& key) { return tree_.lower_bound(key); }

    const_iterator lower_bound(const key_type& key) const { return tree_.lower_bound(key); }

    iterator upper_bound(const key_type& key) { return tree_.upper_bound(key); }

    const_iterator upper_bound(const key_type& key) const { return tree_.upper_bound(key); }

    allocator_type get_allocator() const { return tree_.get_allocator(); }

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

    ft::pair<iterator, iterator> equal_range(const key_type& key)
    {
        return tree_.equal_range_unique(key);
    }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
    {
        return tree_.equal_range_unique(key);
    }

    void swap(map& other) { tree_.swap(other.tree_); }

   private:
    tree_type tree_;
};

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator==(const map<Key, T, Compare, Allocator>& lhs,
                       const map<Key, T, Compare, Allocator>& rhs)
{
    return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
                       const map<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator<(const map<Key, T, Compare, Allocator>& lhs,
                      const map<Key, T, Compare, Allocator>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
                       const map<Key, T, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator>(const map<Key, T, Compare, Allocator>& lhs,
                      const map<Key, T, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
                       const map<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline void swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y)
{
    x.swap(y);
}

}  // namespace ft

#endif  // FT_MAP_HPP
