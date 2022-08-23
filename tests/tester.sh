#!/bin/bash

RESET="\033[0m"
RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"

# exit when any command fails
set -e

run_benchmark()
{
    make clean >/dev/null
    make NAME=tester_ft_container CPPFLAGS="-D NAMESPACE=ft -D BENCHMARK" >/dev/null
    make clean >/dev/null
    make NAME=tester_std_container CPPFLAGS="-D NAMESPACE=std -D BENCHMARK" >/dev/null

    ./tester_ft_container "benchmark" > /dev/null
    ./tester_std_container "benchmark" > /dev/null
}

run_test()
{
    make clean >/dev/null
    make NAME=tester_ft_container CPPFLAGS="-D NAMESPACE=ft" >/dev/null
    make clean >/dev/null
    make NAME=tester_std_container CPPFLAGS="-D NAMESPACE=std" >/dev/null

    mkdir -p logs

    ./tester_ft_container $1 > logs/ft_container_$1.log
    ./tester_std_container $1 > logs/std_container_$1.log

    if ! diff -u logs/std_container_$1.log logs/ft_container_$1.log >diff_$1.diff ;
    then
        printf "${BLUE}$1:${RESET} ${RED}KO${RESET}\n"
    else
        printf "${BLUE}$1:${RESET} ${GREEN}OK${RESET}\n"
    fi
}

run_test_all()
{
    run_test "vector"
    run_test "stack"
    run_test "map"
    run_test "set"
}

clean()
{
    make fclean >/dev/null
    rm -rf tester_ft_container tester_std_container
    rm -rf logs diff_*.diff
}

if [[ ${BASH_ARGV[0]} == "benchmark" ]];
then
    run_benchmark
    clean
    exit
fi

if [[ $# -eq 0 ]];
then
	run_test_all
else
    i=$(($#-1))
    while [ $i -ge 0 ];
    do
        case ${BASH_ARGV[$i]} in
            vector)
                run_test "vector"
                shift;;
            stack)
                run_test "stack"
                shift;;
            map)
                run_test "map"
                shift;;
            set)
                run_test "set"
                shift;;
            all)
                run_test_all
                shift;;
            clean)
                clean
                shift;;
            *)
                printf "${RED}Error${RESET}\ninvalid option: $1\n"
                printf "valid options: vector, stack, map, set, all, benchmark, clean\n"
        esac
        i=$((i-1))
    done
fi

# clean
