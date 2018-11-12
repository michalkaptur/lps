cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
project(palindrome_substring)
set(src main.cpp longest_palindrome_substring.cpp longest_palindrome_substring.hpp)
add_executable(${PROJECT_NAME} ${src})

add_executable(lps_benchmark longest_palindrome_substring.cpp longest_palindrome_substring.hpp benchmark.cpp)
find_package(benchmark REQUIRED CONFIG) #set CMAKE_PREFIX_PATH to benchmark dir
target_link_libraries(lps_benchmark PUBLIC benchmark::benchmark)


