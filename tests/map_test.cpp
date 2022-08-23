#include "tests.hpp"

#define PAIRTYPE NAMESPACE::pair<int, int>
#define INTVEC NAMESPACE::vector<PAIRTYPE>
#define INTMAP NAMESPACE::map<int, int>

//
// TEST-PROTOTYPES
//
void map_test_assign();
void map_test_at();
void map_test_find();
void map_test_insert();
void map_test_erase();
void map_test_count();
void map_test_comp();
void map_test_clear();
void map_test_iterator();
void map_test_riterator();
void map_test_swap();

//
// HELPER-FUNCTIONS
//
template <typename T>
void map_print(const T& map __attribute__((unused)))
{
#ifndef BENCHMARK
    std::cout << "size: " << map.size() << "\n";
    std::cout << "max_size: " << map.max_size() << "\n";
    std::cout << "empty: " << map.empty() << "\n";
    std::cout << "\ncontent_iter:  ";
    for (typename T::const_iterator it = map.begin(); it != map.end(); it++) {
        std::cout << "map[it]: " << (*it).first << " " << (*it).second << ",  ";
    }
    std::cout << std::endl;
#endif
}

//
// MAIN-TEST-FUNCTION
//
void map_test()
{
    map_test_assign();
    map_test_at();
    map_test_find();
    map_test_insert();
    map_test_erase();
    map_test_count();
    map_test_comp();
    map_test_clear();
    map_test_iterator();
    map_test_riterator();
    map_test_swap();
}

void map_test_assign()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(NAMESPACE::make_pair(i, i));
    INTMAP map(vec.begin(), vec.end());
    INTMAP map2(vec.begin() + 2, vec.end() - 1);
    map_print(map);
    map_print(map2);
    map = map2;
    map_print(map);
    map_print(map2);
    map.clear();
    map2 = map;
    map_print(map);
    map_print(map2);
}

void map_test_at()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(NAMESPACE::make_pair(i, i));
    INTMAP map(vec.begin(), vec.end());
    try {
        map.at(10);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    try {
        map.at(1000);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    std::cout << map.at(9) << "\n";
    std::cout << (map.at(0) == map[0]) << "\n";
    std::cout << map.at(1) << std::endl;
    map_print(map);
}

void map_test_find()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(NAMESPACE::make_pair(i, i));
    INTMAP map(vec.begin(), vec.end());
    std::cout << (*(map.find(0))).first << (*(map.find(0))).second << (*(map.find(9))).first
              << (*(map.find(9))).second << "\n";
    std::cout << (map.find(1000) == map.end()) << "\n";
    std::cout << (map.find(0) == map.end()) << "\n";
    std::cout << std::endl;
}

void map_test_insert()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTMAP map;
    map.insert(NAMESPACE::make_pair(10, 10));
    map_print(map);
    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(NAMESPACE::make_pair(i, i));
    map.insert(vec.begin(), vec.end());
    map_print(map);
}

void map_test_erase()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTMAP map;
    for (size_t i = 0; i < 100; i++)
        map.insert(NAMESPACE::make_pair(i, i * 42));
    map_print(map);
    map.erase(map.find(0));
    map_print(map);
    map.erase(map.find(99));
    map_print(map);
    map.erase(++(map.begin()), --(map.end()));
    map_print(map);
    while (map.begin() != map.end())
        map.erase(map.begin());
}

void map_test_count()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTMAP map;
    for (size_t i = 0; i < 100; i++)
        map.insert(NAMESPACE::make_pair(i, i * 42));
    std::cout << map.count(-1) << "\n";
    std::cout << map.count(0) << "\n";
    std::cout << map.count(99) << "\n";
    std::cout << map.count(100) << "\n";
    std::cout << map.count(4158) << "\n";
    std::cout << std::endl;
}

void map_test_comp()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(NAMESPACE::make_pair(i, i));
    INTMAP map(vec.begin(), vec.end());
    INTMAP map2(map);
    std::cout << (map == map2) << "\n";
    std::cout << (map != map2) << "\n";
    std::cout << (map < map2) << "\n";
    std::cout << (map <= map2) << "\n";
    std::cout << (map > map2) << "\n";
    std::cout << (map >= map2) << "\n";
    std::cout << std::endl;
}

void map_test_clear()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTMAP map;
    map.clear();
    map_print(map);
    map.insert(NAMESPACE::make_pair(10, 10));
    map_print(map);
    map.clear();
    map.clear();
    map.clear();
    map_print(map);
}

void map_test_iterator()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(NAMESPACE::make_pair(i, i));
    INTMAP map(vec.begin(), vec.end());
    std::cout << (map.begin() == map.end()) << "\n";
    std::cout << (map.begin() != map.end()) << "\n";
    for (INTMAP::iterator it = map.begin(); it != map.end(); it++)
        std::cout << (*it).first << "  ";
    INTMAP::iterator it = map.begin();
    std::cout << (*(++it)).first << std::endl;
    std::cout << (*(it++)).first << std::endl;
    std::cout << std::endl;
}

void map_test_riterator()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(NAMESPACE::make_pair(i, i));
    INTMAP map(vec.rbegin(), vec.rend());
    std::cout << (map.rbegin() == map.rend()) << "\n";
    std::cout << (map.rbegin() != map.rend()) << "\n";
    for (INTMAP::reverse_iterator rit = map.rbegin(); rit != map.rend(); rit++)
        std::cout << (*rit).first << "  ";
    INTMAP::reverse_iterator rit = map.rbegin();
    std::cout << (*(++rit)).first << std::endl;
    std::cout << (*(rit++)).first << std::endl;
    std::cout << std::endl;
}

void map_test_swap()
{
    PRINT_SEPERATOR();
    PRINT_TEST_FUNC();

    INTMAP map;
    INTMAP map2;
    map2.swap(map);
    map_print(map);
    map_print(map2);
    INTVEC vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
        vec.push_back(NAMESPACE::make_pair(i, i));
    map.insert(vec.begin(), vec.end());
    map.swap(map2);
    map_print(map);
    map_print(map2);
    map2.swap(map);
    map_print(map);
    map_print(map2);
}
