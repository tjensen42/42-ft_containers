#pragma once

#include <map>
#include <set>
#include <stack>
#include <vector>

#include "../map.hpp"
#include "../set.hpp"
#include "../stack.hpp"
#include "../vector.hpp"

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

#ifndef BENCHMARK
#define PRINT_SEPERATOR()                                                                          \
    std::cout << "\n#############################################################################" \
              << "############\n"

#define PRINT_TEST_FUNC() \
    std::cout << "file: " << __FILE__ << "\nfunction: " << __PRETTY_FUNCTION__ << "\n"
#else
#define PRINT_SEPERATOR() ((void)0)
#define PRINT_TEST_FUNC() ((void)0)
#endif

void vector_test();
void stack_test();
void map_test();
void set_test();
