#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

namespace ft {
/*
** true/false_type
*/
struct true_type {
    static const bool value = true;
    typedef true_type type;
};

struct false_type {
    static const bool  value = false;
    typedef false_type type;
};

/*
** enable_if
*/
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};

/*
** remove
*/

template <typename T>
struct remove_const {
    typedef T type;
};

template <typename T>
struct remove_const<const T> {
    typedef T type;
};

template <typename T>
struct remove_volatile {
    typedef T type;
};

template <typename T>
struct remove_volatile<volatile T> {
    typedef T type;
};

template <typename T>
struct remove_cv {
    typedef typename remove_volatile<typename remove_const<T>::type>::type type;
};

/*
** is_integral
*/
template <typename>
struct is_integral_base : public false_type {};

template <>
struct is_integral_base<bool> : public true_type {};

template <>
struct is_integral_base<char> : public true_type {};

template <>
struct is_integral_base<signed char> : public true_type {};

template <>
struct is_integral_base<short int> : public true_type {};

template <>
struct is_integral_base<int> : public true_type {};

template <>
struct is_integral_base<long int> : public true_type {};

template <>
struct is_integral_base<unsigned char> : public true_type {};

template <>
struct is_integral_base<unsigned short int> : public true_type {};

template <>
struct is_integral_base<unsigned int> : public true_type {};

template <>
struct is_integral_base<unsigned long int> : public true_type {};

template <typename T>
struct is_integral : is_integral_base<typename remove_cv<T>::type> {};

/*
**  Compare for equality of types.
*/
template <typename, typename>
struct are_same : public false_type {};

template <typename T>
struct are_same<T, T> : public true_type {};

}  // namespace ft

#endif  // FT_TYPE_TRAITS_HPP
