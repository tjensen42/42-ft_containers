#include "tests.hpp"

#include <unistd.h>

#include <ctime>
#include <iomanip>
#include <iostream>

#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)

void all_tests()
{
    vector_test();
    stack_test();
    map_test();
    set_test();
}

#define BENCHMARK_TESTS 100000

void benchmark()
{
    std::cerr << "\033[0;34mbenchmark namespace: " << STRINGIZE_VALUE_OF(NAMESPACE) << "\033[0m"
              << std::endl;
    // vector
    std::clock_t begin = std::clock();
    for (size_t i = 0; i < BENCHMARK_TESTS; i++) {
        vector_test();
    }
    std::clock_t end = std::clock();
    std::cerr << "\033[0;32m" << STRINGIZE_VALUE_OF(NAMESPACE) << "::vector: " << std::fixed
              << "\033[0m" << std::setprecision(3) << (double(end - begin) / CLOCKS_PER_SEC) << "s"
              << std::endl;
    // stack
    begin = std::clock();
    for (size_t i = 0; i < BENCHMARK_TESTS * 5; i++) {
        stack_test();
    }
    end = std::clock();
    std::cerr << "\033[0;32m" << STRINGIZE_VALUE_OF(NAMESPACE) << "::stack: " << std::fixed
              << "\033[0m" << std::setprecision(3) << (double(end - begin) / CLOCKS_PER_SEC) << "s"
              << std::endl;
    // map
    begin = std::clock();
    for (size_t i = 0; i < BENCHMARK_TESTS; i++) {
        map_test();
    }
    end = std::clock();
    std::cerr << "\033[0;32m" << STRINGIZE_VALUE_OF(NAMESPACE) << "::map: " << std::fixed
              << "\033[0m" << std::setprecision(3) << (double(end - begin) / CLOCKS_PER_SEC) << "s"
              << std::endl;
    // set
    begin = std::clock();
    for (size_t i = 0; i < BENCHMARK_TESTS; i++) {
        set_test();
    }
    end = std::clock();
    std::cerr << "\033[0;32m" << STRINGIZE_VALUE_OF(NAMESPACE) << "::set: " << std::fixed
              << "\033[0m" << std::setprecision(3) << (double(end - begin) / CLOCKS_PER_SEC) << "s"
              << std::endl;
}

int main(int argc, char **argv)
{
    // std::cout << "tested namespace: " << STRINGIZE_VALUE_OF(NAMESPACE);
    if (argc == 1) {
        all_tests();
    } else if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            std::string argv_i = argv[i];
            if (argv_i == "all")
                all_tests();
            else if (argv_i == "vector")
                vector_test();
            else if (argv_i == "stack")
                stack_test();
            else if (argv_i == "map")
                map_test();
            else if (argv_i == "set")
                set_test();
            else if (argv_i == "benchmark")
                benchmark();
            else
                std::cerr << "Invalid argument: " << argv_i << std::endl;
        }
    }
    return 0;
}
