#ifndef FT_RED_BLACK_TREE_HPP
#define FT_RED_BLACK_TREE_HPP

#include <cstddef>
#include <iostream>
#include <string>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

// RED-BLACK TREE
// A self balancing binary search tree (guaranteed height of O(log n) for n
// items)
//
// Rules:
//   1. A node is either red or black
//   2. Root and leaf nodes (NIL nodes) are black
//   3. A red node is either a leaf or has two black children
//   4. All paths from root to leaf must have the same number of black nodes.
//
//  * The longest path is no more than twice the length of the shortest path
//   - shortest: all black nodes
//   - longest: alternating red and black
//
// Operations:
//   1. Search
//   2. Insert, require rotation
//   3. Remove, require rotation
//  * all operations have a time complexity of O(log n)
//

namespace ft
{
template <class NodePtr>
NodePtr RBTree_min(NodePtr node)
{
    while (node->left != nullptr)
        node = node->left;
    return node;
}

template <class NodePtr>
NodePtr RBTree_max(NodePtr node)
{
    while (node->right != nullptr)
        node = node->right;
    return node;
}

template <class NodePtr>
NodePtr RBTree_prev(NodePtr x)
{
    if (x->left != nullptr)
        return RBTree_max(x->left);
    while (x == x->parent->left)
        x = x->parent;
    return x->parent;
}

template <class NodePtr>
NodePtr RBTree_next(NodePtr x)
{
    if (x->right != nullptr)
        return RBTree_min(x->right);
    while (x == x->parent->right)
        x = x->parent;
    return x->parent;
}

enum NODE_COLOR { BLACK, RED };

template <typename T>
struct Node {
   public:
    typedef T                       value_type;
    typedef Node<value_type>*       pointer;
    typedef const Node<value_type>* const_pointer;

   public:
    Node() : val(), color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}

    explicit Node(T key, NODE_COLOR color)
        : val(key), color(color), parent(nullptr), left(nullptr), right(nullptr)
    {
    }

    Node(const Node& x) : val(x.val), color(x.color), parent(x.parent), left(x.left), right(x.right)
    {
    }

   public:
    T          val;
    NODE_COLOR color;
    Node*      parent;
    Node*      left;
    Node*      right;
};

template <typename T, typename DiffType>
class RBTree_const_iterator;

template <typename T, typename DiffType>
class RBTree_iterator
{
   public:
    typedef std::bidirectional_iterator_tag    iterator_category;
    typedef T                                  value_type;
    typedef T&                                 reference;
    typedef T*                                 pointer;
    typedef DiffType                           difference_type;
    typedef RBTree_const_iterator<T, DiffType> const_iterator;

   private:
    typedef typename Node<value_type>::pointer       node_pointer;
    typedef typename Node<value_type>::const_pointer const_node_pointer;

   public:
    RBTree_iterator() : ptr_(NULL) {}

    RBTree_iterator(const RBTree_iterator& other) : ptr_(other.ptr_) {}

    RBTree_iterator(node_pointer p) : ptr_(p) {}

    reference operator*() const { return ptr_->val; }

    pointer operator->() const { return &(operator*()); }

    RBTree_iterator& operator++()
    {
        ptr_ = RBTree_next<node_pointer>(ptr_);
        return *this;
    }

    RBTree_iterator operator++(int)
    {
        RBTree_iterator t = *this;
        ++(*this);
        return t;
    }

    RBTree_iterator& operator--()
    {
        ptr_ = RBTree_prev<node_pointer>(ptr_);
        return *this;
    }

    RBTree_iterator operator--(int)
    {
        RBTree_iterator t = *this;
        --(*this);
        return t;
    }

    bool operator==(const RBTree_iterator& other) const { return ptr_ == other.ptr_; }

    bool operator==(const const_iterator& other) const { return ptr_ == other.base(); }

    bool operator!=(const RBTree_iterator& other) const { return !(*this == other); }

    bool operator!=(const const_iterator& other) const { return !(*this == other); }

    node_pointer base() const { return ptr_; }

   private:
    node_pointer ptr_;
};

template <typename T, typename DiffType>
class RBTree_const_iterator
{
   public:
    typedef std::bidirectional_iterator_tag           iterator_category;
    typedef T                                         value_type;
    typedef const T&                                  reference;
    typedef const T*                                  pointer;
    typedef DiffType                                  difference_type;
    typedef ft::RBTree_iterator<value_type, DiffType> non_const_iterator;

   private:
    typedef typename Node<value_type>::pointer       node_pointer;
    typedef typename Node<value_type>::const_pointer const_node_pointer;

   public:
    RBTree_const_iterator() : ptr_(nullptr) {}

    RBTree_const_iterator(const non_const_iterator& other) : ptr_(other.base()) {}

    RBTree_const_iterator(const RBTree_const_iterator& other) : ptr_(other.ptr_) {}

    RBTree_const_iterator(const_node_pointer p) : ptr_(p) {}

    reference operator*() const { return ptr_->val; }

    pointer operator->() const { return &(operator*()); }

    RBTree_const_iterator& operator++()
    {
        ptr_ = RBTree_next<const_node_pointer>(ptr_);
        return *this;
    }

    RBTree_const_iterator operator++(int)
    {
        RBTree_const_iterator t = *this;
        ++(*this);
        return t;
    }

    RBTree_const_iterator& operator--()
    {
        ptr_ = RBTree_prev<const_node_pointer>(ptr_);
        return *this;
    }

    RBTree_const_iterator operator--(int)
    {
        RBTree_const_iterator t = *this;
        --(*this);
        return t;
    }

    bool operator==(const RBTree_const_iterator& other) const { return ptr_ == other.ptr_; }

    bool operator==(const non_const_iterator& other) const { return ptr_ == other.base(); }

    bool operator!=(const RBTree_const_iterator& other) const { return !(*this == other); }

    bool operator!=(const non_const_iterator& other) const { return !(*this == other); }

    const_node_pointer base() const { return ptr_; }

   private:
    const_node_pointer ptr_;
};

template <typename T, typename Compare, typename Allocator>
class RBTree
{
   public:
    typedef T                                                          value_type;
    typedef Compare                                                    value_compare;
    typedef Allocator                                                  allocator_type;
    typedef Node<value_type>                                           node_type;
    typedef typename node_type::pointer                                node_pointer;
    typedef typename node_type::const_pointer                          const_node_pointer;
    typedef typename allocator_type::template rebind<node_type>::other node_allocator_type;
    typedef typename allocator_type::pointer                           pointer;
    typedef typename allocator_type::const_pointer                     const_pointer;
    typedef typename allocator_type::size_type                         size_type;
    typedef typename allocator_type::difference_type                   difference_type;
    typedef ft::RBTree_iterator<value_type, difference_type>           iterator;
    typedef ft::RBTree_const_iterator<value_type, difference_type>     const_iterator;
    typedef ft::reverse_iterator<iterator>                             reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                       const_reverse_iterator;

   protected:
    value_compare       value_compare_;
    allocator_type      value_alloc_;
    node_allocator_type node_alloc_;
    node_pointer        head_;
    node_pointer        left_most_;
    size_type           node_count_;

   public:
    explicit RBTree(const value_compare& comp, const allocator_type& alloc)
        : value_compare_(comp), value_alloc_(alloc), node_alloc_(alloc), node_count_(0)
    {
        head_ = construct_node_(value_type(), BLACK);
        head_->parent = head_;
        left_most_ = head_;
    }

    RBTree(const RBTree& other)
        : value_compare_(other.value_compare_),
          value_alloc_(other.value_alloc_),
          node_alloc_(other.node_alloc_),
          node_count_(other.node_count_)
    {
        head_ = construct_node_(value_type(), BLACK);
        head_->parent = head_;
        left_most_ = head_;
        *this = other;
    }

    ~RBTree() { destroy_(head_); }

    RBTree& operator=(const RBTree& other)
    {
        if (this != &other) {
            clear();
            value_compare_ = other.value_compare_;
            if (other.root_() != nullptr) {
                root_() = copy_(other.root_());
                root_()->parent = head_;
                left_most_ = RBTree_min(root_());
                node_count_ = other.node_count_;
            }
        }
        return *this;
    }

    iterator begin() { return iterator(left_most_); }

    const_iterator begin() const { return const_iterator(left_most_); }

    iterator end() { return iterator(end_node_()); }

    const_iterator end() const { return const_iterator(end_node_()); }

    template <typename Key>
    iterator find(const Key& key)
    {
        node_pointer tmp = root_();
        while (tmp != nullptr) {
            if (value_compare_(key, tmp->val))
                tmp = tmp->left;
            else if (value_compare_(tmp->val, key))
                tmp = tmp->right;
            else
                return tmp;
        }
        return end();
    }

    template <typename Key>
    const_iterator find(const Key& key) const
    {
        node_pointer tmp = root_();
        while (tmp != nullptr) {
            if (value_compare_(key, tmp->val))
                tmp = tmp->left;
            else if (value_compare_(tmp->val, key))
                tmp = tmp->right;
            else
                return tmp;
        }
        return end();
    }

    size_type size() const { return node_count_; }

    ft::pair<iterator, bool> insert_unique(const value_type& val)
    {
        node_pointer  parent;
        node_pointer& pos_ptr_ref = find_key_or_new_pos(parent, val);
        node_pointer  pos_ptr = pos_ptr_ref;
        bool          inserted = false;
        if (pos_ptr_ref == nullptr) {
            node_pointer new_node = construct_node_(val, RED);
            insert_node_at_(new_node, pos_ptr_ref, parent);
            inserted = true;
            pos_ptr = new_node;
        }
        return ft::make_pair(iterator(pos_ptr), inserted);
    }

    iterator insert_unique(const_iterator hint, const value_type& val)
    {
        node_pointer  parent;
        node_pointer& pos_ptr_ref = find_key_or_new_pos(hint, parent, val);
        node_pointer  pos_ptr = pos_ptr_ref;
        if (pos_ptr_ref == nullptr) {
            node_pointer new_node = construct_node_(val, RED);
            insert_node_at_(new_node, pos_ptr_ref, parent);
            pos_ptr = new_node;
        }
        return iterator(pos_ptr);
    }

    template <class InputIterator>
    void insert_unique_range(InputIterator first, InputIterator last)
    {
        for (; first != last; ++first)
            insert_unique(*first);
    }

    template <typename Key>
    iterator lower_bound(const Key& key)
    {
        node_pointer result = end_node_();
        node_pointer iter = root_();
        while (iter != nullptr) {
            if (!value_compare_(iter->val, key)) {
                result = iter;
                iter = iter->left;
            } else
                iter = iter->right;
        }
        return iterator(result);
    }

    template <typename Key>
    const_iterator lower_bound(const Key& key) const
    {
        node_pointer result = end_node_();
        node_pointer iter = root_();
        while (iter != nullptr) {
            if (!value_compare_(iter->val, key)) {
                result = iter;
                iter = iter->left;
            } else
                iter = iter->right;
        }
        return const_iterator(result);
    }

    template <typename Key>
    iterator upper_bound(const Key& key)
    {
        node_pointer result = end_node_();
        node_pointer iter = root_();
        while (iter != nullptr) {
            if (value_compare_(key, iter->val)) {
                result = iter;
                iter = iter->left;
            } else
                iter = iter->right;
        }
        return iterator(result);
    }

    template <typename Key>
    const_iterator upper_bound(const Key& key) const
    {
        node_pointer result = end_node_();
        node_pointer iter = root_();
        while (iter != nullptr) {
            if (value_compare_(key, iter->val)) {
                result = iter;
                iter = iter->left;
            } else
                iter = iter->right;
        }
        return const_iterator(result);
    }

    template <typename Key>
    ft::pair<iterator, iterator> equal_range_unique(const Key& key)
    {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    template <typename Key>
    ft::pair<const_iterator, const_iterator> equal_range_unique(const Key& key) const
    {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    void clear()
    {
        destroy_(root_());
        root_() = nullptr;
        left_most_ = end_node_();
        node_count_ = 0;
    }

    iterator erase_node(const_iterator node)
    {
        node_pointer node_ptr = const_cast<node_pointer>(node.base());
        node_pointer next_node_ptr = RBTree_next(node_ptr);
        if (node_ptr == left_most_)
            left_most_ = next_node_ptr;
        remove_node_(root_(), node_ptr);
        destroy_node_(node_ptr);
        --node_count_;
        return iterator(next_node_ptr);
    }

    void erase_range(const_iterator first, const_iterator last)
    {
        while (first != last)
            first = erase_node(first);
    }

    template <typename Key>
    size_type erase_unique(const Key& key)
    {
        iterator node = find(key);
        if (node == end())
            return 0;
        erase_node(node);
        return 1;
    }

    allocator_type get_allocator() const { return value_alloc_; }

    size_type max_size() const { return node_alloc_.max_size(); }

    void swap(RBTree& other)
    {
        ft::swap(value_compare_, other.value_compare_);
        ft::swap(value_alloc_, other.value_alloc_);
        ft::swap(node_alloc_, other.node_alloc_);
        ft::swap(head_, other.head_);
        ft::swap(left_most_, other.left_most_);
        ft::swap(node_count_, other.node_count_);
    }

    void print() { print_from_node_(root_()); }

   private:
    node_pointer& end_node_() { return head_; }

    node_pointer end_node_() const { return head_; }

    node_pointer& root_() { return end_node_()->left; }

    node_pointer root_() const { return end_node_()->left; }

    void rotate_left_(node_pointer x)
    {
        node_pointer y = x->right;
        x->right = y->left;
        if (x->right != nullptr)
            x->right->parent = x;
        y->parent = x->parent;
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotate_right_(node_pointer x)
    {
        node_pointer y = x->left;
        x->left = y->right;
        if (x->left != nullptr)
            x->left->parent = x;
        y->parent = x->parent;
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void destroy_node_(node_pointer node)
    {
        value_alloc_.destroy(&node->val);
        node_alloc_.deallocate(node, 1);
    }

    void destroy_(node_pointer node)
    {
        if (node != nullptr) {
            destroy_(node->left);
            destroy_(node->right);
            destroy_node_(node);
        }
    }

    node_pointer copy_(const node_pointer node)
    {
        if (node == nullptr)
            return nullptr;
        node_pointer new_node = construct_node_(node);
        new_node->left = copy_(node->left);
        if (new_node->left != nullptr)
            new_node->left->parent = new_node;
        new_node->right = copy_(node->right);
        if (new_node->right != nullptr)
            new_node->right->parent = new_node;
        return new_node;
    }

    template <typename Key>
    node_pointer& find_key_or_new_pos(node_pointer& parent, const Key& key)
    {
        node_pointer iter = root_();
        if (iter != nullptr) {
            while (true) {
                if (value_compare_(key, iter->val)) {
                    if (iter->left != nullptr)
                        iter = iter->left;
                    else {
                        parent = iter;
                        return parent->left;
                    }
                } else if (value_compare_(iter->val, key)) {
                    if (iter->right != nullptr)
                        iter = iter->right;
                    else {
                        parent = iter;
                        return parent->right;
                    }
                } else {
                    parent = iter;
                    return parent;
                }
            }
        }
        parent = end_node_();
        return parent->left;
    }

    template <typename Key>
    node_pointer& find_key_or_new_pos(const_iterator hint, node_pointer& parent, const Key& key)
    {
        if (hint == end() || value_compare_(key, *hint)) {
            const_iterator prior = hint;
            if (prior == begin() || value_compare_(*(--prior), key)) {
                if (hint.base()->left == nullptr) {
                    parent = const_cast<node_pointer>(hint.base());
                    return parent->left;
                } else {
                    parent = const_cast<node_pointer>(prior.base());
                    return parent->right;
                }
            }
            return find_key_or_new_pos(parent, key);
        } else if (value_compare_(*hint, key)) {
            const_iterator next = ft::next(hint);
            if (next == end() || value_compare_(key, *next)) {
                if (hint.base()->right == nullptr) {
                    parent = const_cast<node_pointer>(hint.base());
                    return parent->right;
                } else {
                    parent = const_cast<node_pointer>(next.base());
                    return parent->left;
                }
            }
            return find_key_or_new_pos(parent, key);
        }
        parent = const_cast<node_pointer>(hint.base());
        return parent;
    }

    node_pointer construct_node_(const node_pointer& other)
    {
        return (construct_node_(other->val, other->color));
    }

    node_pointer construct_node_(const value_type& val, NODE_COLOR color)
    {
        node_pointer new_node = node_alloc_.allocate(1);
        value_alloc_.construct(&new_node->val, val);
        new_node->color = color;
        new_node->parent = nullptr;
        new_node->left = nullptr;
        new_node->right = nullptr;
        return new_node;
    }

    void insert_node_at_(node_pointer new_node, node_pointer& pos, node_pointer parent)
    {
        new_node->parent = parent;
        pos = new_node;
        if (left_most_->left != nullptr)
            left_most_ = left_most_->left;
        balance_after_insert_(root_(), new_node);
        ++node_count_;
    }

    void balance_after_insert_(node_pointer root, node_pointer k)
    {
        k->color = (k == root) ? BLACK : RED;
        while (k != root && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                node_pointer uncle = k->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    uncle->color = BLACK;
                    k = k->parent;
                    k->color = BLACK;
                    k = k->parent;
                    k->color = (k == root) ? BLACK : RED;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        rotate_left_(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotate_right_(k->parent->parent);
                    break;
                }
            } else {
                node_pointer uncle = k->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    uncle->color = BLACK;
                    k = k->parent;
                    k->color = BLACK;
                    k = k->parent;
                    k->color = (k == root) ? BLACK : RED;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotate_right_(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotate_left_(k->parent->parent);
                    break;
                }
            }
        }
    }

    void remove_node_(node_pointer root, node_pointer node)
    {
        node_pointer repl =
            (node->left == nullptr || node->right == nullptr) ? node : RBTree_next(node);
        node_pointer repl_child = repl->left != nullptr ? repl->left : repl->right;
        node_pointer sibling = nullptr;
        if (repl_child != nullptr)
            repl_child->parent = repl->parent;
        if (repl == repl->parent->left) {
            repl->parent->left = repl_child;
            if (repl == root)
                root = repl_child;
            else
                sibling = repl->parent->right;
        } else {
            repl->parent->right = repl_child;
            sibling = repl->parent->left;
        }
        bool removed_black = (repl->color == BLACK);
        if (repl != node) {
            if (node == root)
                root = repl;
            repl->parent = node->parent;
            if (node == node->parent->left)
                repl->parent->left = repl;
            else
                repl->parent->right = repl;
            repl->left = node->left;
            repl->left->parent = repl;
            repl->right = node->right;
            if (repl->right != nullptr)
                repl->right->parent = repl;
            repl->color = node->color;
        }
        if (removed_black && root != nullptr) {
            if (repl_child != nullptr)
                repl_child->color = BLACK;
            else
                balance_after_remove_(root, sibling);
        }
    }

    void balance_after_remove_(node_pointer root, node_pointer sibling)
    {
        node_pointer x = nullptr;
        while (true) {
            if (sibling == sibling->parent->right) {
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    sibling->parent->color = RED;
                    rotate_left_(sibling->parent);
                    if (root == sibling->left)
                        root = sibling;
                    sibling = sibling->left->right;
                }
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    x = sibling->parent;
                    if (x == root || x->color == RED) {
                        x->color = BLACK;
                        break;
                    }
                    sibling = (x == x->parent->left) ? x->parent->right : x->parent->left;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotate_right_(sibling);
                        sibling = sibling->parent;
                    }
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    rotate_left_(sibling->parent);
                    break;
                }
            } else {
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    sibling->parent->color = RED;
                    rotate_right_(sibling->parent);
                    if (root == sibling->right)
                        root = sibling;
                    sibling = sibling->right->left;
                }
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    x = sibling->parent;
                    if (x == root || x->color == RED) {
                        x->color = BLACK;
                        break;
                    }
                    sibling = (x == x->parent->left) ? x->parent->right : x->parent->left;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotate_left_(sibling);
                        sibling = sibling->parent;
                    }
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rotate_right_(sibling->parent);
                    break;
                }
            }
        }
    }

    void print_from_node_(node_pointer node, const std::string& prefix = "", bool is_left = false,
                          bool is_first = true)
    {
        if (node != nullptr) {
            print_from_node_(node->right, prefix + (is_first ? " " : "    "), false, false);
            std::cout << prefix;
            if (!is_first)
                std::cout << (is_left ? "└──" : "┌──");
            if (node->color == BLACK)
                std::cout << node->val.first << std::endl;
            else
                std::cout << "\033[0;31m" << node->val.first << "\033[0m" << std::endl;
            print_from_node_(node->left, prefix + (is_first ? " " : "    "), true, false);
        }
    }
};

}  // namespace ft

#endif  // FT_RED_BLACK_TREE_HPP
