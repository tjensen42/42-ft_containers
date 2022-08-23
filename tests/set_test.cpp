#include "tests.hpp"

#define INTVEC NAMESPACE::vector<int>
#define INTSET NAMESPACE::set<int>

//
// TEST-PROTOTYPES
//
void set_test_assign();
void set_test_find();
void set_test_insert();
void set_test_erase();
void set_test_count();
void set_test_comp();
void set_test_clear();
void set_test_iterator();
void set_test_riterator();
void set_test_swap();

//
// HELPER-FUNCTIONS
//
template <typename T>
void set_print(const T& set __attribute__((unused)))
{
#ifndef BENCHMARK
    std::cout << "size: " << set.size() << "\n";
    std::cout << "max_size: " << set.max_size() << "\n";
    std::cout << "empty: " << set.empty() << "\n";
    std::cout << "\ncontent_iter:  ";
    for (typename T::const_iterator it = set.begin(); it != set.end(); it++) {
        std::cout << "set[it]: " << (*it) << ",  ";
    }
    std::cout << std::endl;
#endif
}

//
// MAIN-TEST-FUNCTION
//
void set_test()
{
    set_test_assign();
    set_test_find();
    set_test_insert();
    set_test_erase();
    set_test_count();
    set_test_comp();
    set_test_clear();
    set_test_iterator();
    set_test_riterator();
    set_test_swap();
}

void set_test_assign()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    INTSET set(vec.begin(), vec.end());
    INTSET set2(vec.begin() + 2, vec.end() - 1);
    set_print(set);
    set_print(set2);
    set = set2;
    set_print(set);
    set_print(set2);
    set.clear();
    set2 = set;
    set_print(set);
    set_print(set2);
}

void set_test_find()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    INTSET set(vec.begin(), vec.end());
    std::cout << (*(set.find(0))) << (*(set.find(0))) << (*(set.find(9))) << (*(set.find(9)))
              << "\n";
    std::cout << (set.find(1000) == set.end()) << "\n";
    std::cout << (set.find(0) == set.end()) << "\n";
    std::cout << std::endl;
}

void set_test_insert()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTSET set;
    set.insert(10);
    set_print(set);
    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    set.insert(vec.begin(), vec.end());
    set_print(set);
}

void set_test_erase()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTSET set;
    for (size_t i = 0; i < 100; i++)
        set.insert(i);
    set_print(set);
    set.erase(set.find(0));
    set_print(set);
    set.erase(set.find(99));
    set_print(set);
    set.erase(++(set.begin()), --(set.end()));
    set_print(set);
    while (set.begin() != set.end())
        set.erase(set.begin());
}

void set_test_count()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTSET set;
    for (size_t i = 0; i < 100; i++)
        set.insert(i);
    std::cout << set.count(-1) << "\n";
    std::cout << set.count(0) << "\n";
    std::cout << set.count(99) << "\n";
    std::cout << set.count(100) << "\n";
    std::cout << set.count(4158) << "\n";
    std::cout << std::endl;
}

void set_test_comp()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    INTSET set(vec.begin(), vec.end());
    INTSET set2(set);
    std::cout << (set == set2) << "\n";
    std::cout << (set != set2) << "\n";
    std::cout << (set < set2) << "\n";
    std::cout << (set <= set2) << "\n";
    std::cout << (set > set2) << "\n";
    std::cout << (set >= set2) << "\n";
    std::cout << std::endl;
}

void set_test_clear()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTSET set;
    set.clear();
    set_print(set);
    set.insert(10);
    set_print(set);
    set.clear();
    set.clear();
    set.clear();
    set_print(set);
}

void set_test_iterator()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    INTSET set(vec.begin(), vec.end());
    std::cout << (set.begin() == set.end()) << "\n";
    std::cout << (set.begin() != set.end()) << "\n";
    for (INTSET::iterator it = set.begin(); it != set.end(); it++)
        std::cout << (*it) << "  ";
    INTSET::iterator it = set.begin();
    std::cout << (*(++it)) << std::endl;
    std::cout << (*(it++)) << std::endl;
    std::cout << std::endl;
}

void set_test_riterator()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    INTSET set(vec.rbegin(), vec.rend());
    std::cout << (set.rbegin() == set.rend()) << "\n";
    std::cout << (set.rbegin() != set.rend()) << "\n";
    for (INTSET::reverse_iterator rit = set.rbegin(); rit != set.rend(); rit++)
        std::cout << (*rit) << "  ";
    INTSET::reverse_iterator rit = set.rbegin();
    std::cout << (*(++rit)) << std::endl;
    std::cout << (*(rit++)) << std::endl;
    std::cout << std::endl;
}

void set_test_swap()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTSET set;
    INTSET set2;
    set2.swap(set);
    set_print(set);
    set_print(set2);
    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    set.insert(vec.begin(), vec.end());
    set.swap(set2);
    set_print(set);
    set_print(set2);
    set2.swap(set);
    set_print(set);
    set_print(set2);
}
