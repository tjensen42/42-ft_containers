#include <iostream>
#include <vector>

#include "tests.hpp"

#define INTVEC NAMESPACE::vector<int>
#define STRVEC NAMESPACE::vector<std::string>
#define DBLVEC NAMESPACE::vector<double>

//
// TEST-PROTOTYPES
//
void vector_test_assign();
void vector_test_at();
void vector_test_back();
void vector_test_clear();
void vector_test_compare();
void vector_test_constructor();
void vector_test_erase();
void vector_test_front();
void vector_test_insert();
void vector_test_iterator();
void vector_test_push_pop();
void vector_test_resize();
void vector_test_riterator();
void vector_test_swap();

//
// HELPER-FUNCTIONS
//
template <typename T>
void vec_print(const T& vec __attribute__((unused)))
{
#ifndef BENCHMARK
    std::cout << "size: " << vec.size() << "\n";
    std::cout << "max_size: " << vec.max_size() << "\n";
    std::cout << "capacity: " << vec.capacity() << "\n";
    std::cout << "empty: " << vec.empty() << "\n";
    if (vec.size() > 0)
        std::cout << "vec.front(): " << vec.front() << "vec.back()" << vec.back() << std::endl;
    std::cout << "\ncontent_index: ";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << "vec[" << i << "]: " << vec[i] << "  ";
    }
    std::cout << "\ncontent_iter:  ";
    for (typename T::const_iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << "vec[" << it - vec.begin() << "]: " << *it << "  ";
    }
    std::cout << std::endl;
#endif
}

//
// MAIN-TEST-FUNCTION
//
void vector_test()
{
    vector_test_assign();
    vector_test_at();
    vector_test_back();
    vector_test_clear();
    vector_test_compare();
    vector_test_constructor();
    vector_test_erase();
    vector_test_front();
    vector_test_insert();
    vector_test_iterator();
    vector_test_push_pop();
    vector_test_push_pop();
    vector_test_resize();
    vector_test_riterator();
    vector_test_swap();
}

//
// TEST-FUNCTIONS
//
void vector_test_assign()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec;
    vec_print(ivec);
    ivec.assign(10, 42);
    vec_print(ivec);
    ivec.assign(8, 42);
    vec_print(ivec);
    ivec.assign(0, 42);
    vec_print(ivec);
    ivec.assign(100, 42);
    vec_print(ivec);

    STRVEC strvec;
    vec_print(strvec);
    strvec.assign(10, "42");
    vec_print(strvec);
    strvec.assign(8, "42");
    vec_print(strvec);
    strvec.assign(0, "42");
    vec_print(strvec);
    strvec.assign(100, "42");
    vec_print(strvec);

    std::vector<int> i_std_vec;
    i_std_vec.reserve(42);
    for (size_t i = 0; i < 42; i++) {
        i_std_vec.push_back(i);
    }
    ivec.assign(i_std_vec.begin(), i_std_vec.end());
    vec_print(strvec);
    ivec.assign(i_std_vec.begin(), i_std_vec.begin() + 3);
    vec_print(strvec);
    ivec.assign(i_std_vec.end(), i_std_vec.end());
    vec_print(strvec);
}

void vector_test_at()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec(10, 42);
    try {
        ivec.at(10);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    try {
        ivec.at(1000);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    std::cout << ivec.at(9) << "\n";
    std::cout << (ivec.at(0) == ivec[0]) << "\n";
    std::cout << ivec.at(1) << std::endl;
}

void vector_test_back()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec(1, 42);
    std::cout << (ivec.front() == ivec.back());
    std::cout << (ivec[0] == ivec.back());
    std::cout << (&(ivec[0]) == &(ivec.back()));
    vec_print(ivec);
    INTVEC ivec2(2, 42);
    std::cout << (ivec2.front() == ivec2.back());
    vec_print(ivec2);
}

void vector_test_clear()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec;
    ivec.clear();
    vec_print(ivec);
    ivec.assign(10, 42);
    ivec.clear();
    ivec.clear();
    ivec.clear();
    vec_print(ivec);
}

void vector_test_compare()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec(10, 42);
    INTVEC ivec2(10, 42);
    std::cout << (ivec == ivec2) << std::endl;
    std::cout << (ivec != ivec2) << std::endl;
    std::cout << (ivec < ivec2) << std::endl;
    std::cout << (ivec > ivec2) << std::endl;
    std::cout << (ivec <= ivec2) << std::endl;
    std::cout << (ivec >= ivec2) << std::endl;
    ivec.assign(10, 42);
    ivec2.assign(3, 10);
    std::cout << (ivec == ivec2) << std::endl;
    std::cout << (ivec != ivec2) << std::endl;
    std::cout << (ivec < ivec2) << std::endl;
    std::cout << (ivec > ivec2) << std::endl;
    std::cout << (ivec <= ivec2) << std::endl;
    std::cout << (ivec >= ivec2) << std::endl;
    ivec.assign(3, 11);
    ivec2.assign(5, 10);
    std::cout << (ivec == ivec2) << std::endl;
    std::cout << (ivec != ivec2) << std::endl;
    std::cout << (ivec < ivec2) << std::endl;
    std::cout << (ivec > ivec2) << std::endl;
    std::cout << (ivec <= ivec2) << std::endl;
    std::cout << (ivec >= ivec2) << std::endl;
}

void vector_test_constructor()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec;
    INTVEC ivec_cpy(ivec);
    vec_print(ivec);
    vec_print(ivec_cpy);
    INTVEC ivec2(10, 42);
    INTVEC ivec2_cpy(ivec2);
    vec_print(ivec2);
    vec_print(ivec2_cpy);
    std::vector<int> std_vec(100, 42);
    INTVEC           ivec3(std_vec.begin(), std_vec.end());
    INTVEC           ivec3_cpy(ivec2);
    vec_print(ivec3);
    vec_print(ivec3_cpy);
}

void vector_test_erase()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec(12, 42);
    vec_print(ivec);
    ivec.erase(ivec.begin());
    vec_print(ivec);
    ivec.erase(ivec.begin(), ivec.begin() + 4);
    vec_print(ivec);
    for (INTVEC::iterator it = ivec.begin(); it != ivec.end(); it = ivec.begin())
        ivec.erase(it);
    vec_print(ivec);
}

void vector_test_front()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec(1, 42);
    std::cout << (ivec[0] == ivec.front());
    std::cout << (&(ivec[0]) == &(ivec.front()));
    vec_print(ivec);
    INTVEC ivec2(2, 42);
    std::cout << (ivec2.front() == ivec2.back());
    std::cout << (&(ivec2[0]) == &(ivec2.front()));
    vec_print(ivec2);
}

void vector_test_insert()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec;
    ivec.insert(ivec.begin(), 2);
    ivec.insert(ivec.begin(), 1);
    ivec.insert(ivec.end(), 3);
    vec_print(ivec);
    ivec.insert(ivec.begin() + 1, 3, 42);
    vec_print(ivec);
}

void vector_test_iterator()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec;
    std::cout << (ivec.begin() != ivec.end()) << "\n";
    ivec.resize(10, 10);
    std::cout << (ivec.begin() < ivec.end()) << "\n";
    std::cout << (ivec.begin() > ivec.end()) << "\n";
    std::cout << (ivec.begin() == ivec.end()) << "\n";
    for (INTVEC::iterator it = ivec.begin(); it != ivec.end(); it++)
        std::cout << *it << "  ";
    INTVEC::iterator it = ivec.begin() + 4;
    std::cout << *(it) << "\n";
    std::cout << *(it).base() << "\n";
    std::cout << *(it - 0) << "\n";
    std::cout << *(it - 0).base() << "\n";
    std::cout << *(it - 1).base() << "\n";
    std::cout << "\n";
    INTVEC::const_iterator cit = ivec.begin() + 4;
    std::cout << *(cit) << "\n";
    std::cout << *(cit).base() << "\n";
    std::cout << *(cit - 0) << "\n";
    std::cout << *(cit - 0).base() << "\n";
    std::cout << *(cit - 1).base() << "\n";
    std::cout << std::endl;
}

void vector_test_push_pop()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    STRVEC str_vec;
    str_vec.push_back("4242");
    for (size_t i = 0; i < 10; i++)
        str_vec.push_back("Test 42 ");
    vec_print(str_vec);
    for (size_t i = 0; i < 3; i++)
        str_vec.pop_back();
    vec_print(str_vec);
    str_vec.pop_back();
    str_vec.pop_back();
    str_vec.pop_back();
    str_vec.pop_back();
    vec_print(str_vec);
    str_vec.pop_back();
}

void vector_test_resize()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec;
    ivec.resize(10, 10);
    vec_print(ivec);
    ivec.resize(5, 5);
    vec_print(ivec);
    ivec.resize(100, 100);
    vec_print(ivec);

    INTVEC ivec2(ivec);
    ivec2.resize(10, 10);
    vec_print(ivec2);
    ivec2.resize(0, 10);
    vec_print(ivec2);
}

void vector_test_riterator()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec;
    std::cout << (ivec.rbegin() != ivec.rend()) << "\n";
    ivec.resize(10, 10);
    std::cout << (ivec.rbegin() < ivec.rend()) << "\n";
    std::cout << (ivec.rbegin() > ivec.rend()) << "\n";
    std::cout << (ivec.rbegin() == ivec.rend()) << "\n";
    for (INTVEC::reverse_iterator rit = ivec.rbegin(); rit != ivec.rend(); rit++)
        std::cout << *rit << "  ";
    INTVEC::reverse_iterator rit = ivec.rbegin() + 4;
    std::cout << *(rit) << std::endl;
    std::cout << *(rit).base() << std::endl;
    std::cout << *(rit - 0) << std::endl;
    std::cout << *(rit - 0).base() << std::endl;
    std::cout << *(rit - 1).base() << std::endl;
    std::cout << std::endl;
}

void vector_test_swap()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC ivec(10, 10);
    INTVEC ivec2(42, 42);
    vec_print(ivec);
    vec_print(ivec2);

    ivec2.swap(ivec);
    vec_print(ivec);
    vec_print(ivec2);

    ivec.swap(ivec2);
    vec_print(ivec);
    vec_print(ivec2);

    ivec.resize(4);
    ivec.swap(ivec2);
    vec_print(ivec);
    vec_print(ivec2);
}
