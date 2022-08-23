#include "tests.hpp"

#define INTVEC NAMESPACE::vector<int>
#define INTSTACK NAMESPACE::stack<int, INTVEC>

//
// HELPER-FUNCTIONS
//
template <typename T>
void stack_print(const T& st __attribute__((unused)))
{
#ifndef BENCHMARK
    std::cout << "size: " << st.size() << "\n";
    std::cout << "empty: " << st.empty() << "\n";
    std::cout << "\ncontent: ";
    T      stack_cpy(st);
    size_t i = 0;
    while (stack_cpy.empty() == false) {
        std::cout << i << ": " << stack_cpy.top() << "  ";
        stack_cpy.pop();
        i++;
    }
    std::cout << std::endl;
#endif
}

//
// MAIN-TEST-FUNCTION
//
void stack_test()
{
    INTSTACK st;

    st.push(42);
    for (size_t i = 0; i < 100; i++)
        st.push(i);
    st.push(42);
    stack_print(st);
    st.pop();
    st.pop();
    st.pop();
    stack_print(st);
    INTVEC   vec(10, 42);
    INTSTACK st2(vec);
    stack_print(st2);
    st = st2;
    stack_print(st2);
#ifndef BENCHMARK
    std::cout << (st == st2) << "\n";
    std::cout << (st != st2) << "\n";
    std::cout << (st < st2) << "\n";
    std::cout << (st <= st2) << "\n";
    std::cout << (st > st2) << "\n";
    std::cout << (st >= st2) << "\n";
    st.pop();
    std::cout << (st == st2) << "\n";
    std::cout << (st != st2) << "\n";
    std::cout << (st < st2) << "\n";
    std::cout << (st <= st2) << "\n";
    std::cout << (st > st2) << "\n";
    std::cout << (st >= st2) << "\n";
#endif
}
