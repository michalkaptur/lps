#include <iostream>
#include <iterator>
#include <string>

#define CATCH_CONFIG_MAIN
#include "externals/catch.hpp"

bool is_palindrome(const std::string& s) {
    auto begin = s.begin();
    auto end = s.rbegin();
    while (std::distance(begin, end.base()) > 0){
        if (*begin != *end){
            return false;
        }
        std::advance(begin, 1);
        std::advance(end, 1);
        // fixme: could stop in the middle
    }
    return true;
}

std::size_t longest_even_palindrome_substring(const auto center_it, const std::string& input){
    std::size_t benchmark = 0;
    if (std::next(center_it) == input.end()){
        return benchmark;
    }

    auto left = center_it;
    auto right = std::next(center_it, 2);

    if (left == input.begin() or right == input.end()){
        std::string candidate(left, right);
        return std::max(benchmark, candidate.length());
    }

    do {
        std::string candidate(left, right);
        if (is_palindrome(candidate)){
            benchmark = std::max(benchmark, candidate.length());
        } else {
            break;
        }
        std::advance(right, 1);
        std::advance(left, -1);
    }
    while(right != input.end() and left != input.begin());
    std::string candidate(left, right);
    if (is_palindrome(candidate)){
        benchmark = std::max(benchmark, candidate.length());
    }
    return benchmark;
}

std::size_t longest_odd_palindrome_substring(const auto center_it, const std::string& input){
    std::size_t benchmark = 0;
    auto left = center_it;
    if (left == input.end())
    {
        return benchmark;
    }

    auto right = std::next(center_it, 1);
    if (right == input.end()){
        return 1;
    }


    do {
        std::string candidate(left, right);
        if (is_palindrome(candidate)){
            benchmark = std::max(benchmark, candidate.length());
        } else {
            break;
        }
        std::advance(right, 1);
        std::advance(left, -1);
    }
    while(right != input.end() and left != input.begin());
    std::string candidate(left, right);
    if (is_palindrome(candidate)){
        benchmark = std::max(benchmark, candidate.length());
    }
    return benchmark;
}



unsigned longest_palindrome_substring(const std::string& input) {
    std::size_t benchmark = input.empty() ? 0 : 1;
    auto center = input.begin();
    while (center != input.end()) {
        benchmark = std::max(benchmark, longest_odd_palindrome_substring(center, input));
        benchmark = std::max(benchmark, longest_even_palindrome_substring(center, input));
        std::advance(center, 1);
    }
    return benchmark;
}

TEST_CASE("found longest palindrome", "[palindrome]") {
    REQUIRE(longest_palindrome_substring("") == 0);
    REQUIRE(longest_palindrome_substring("abba") == 4);
    REQUIRE(longest_palindrome_substring("aa") == 2);
    REQUIRE(longest_palindrome_substring("1234xxyybbbbyyxx12") == 12);
    REQUIRE(longest_palindrome_substring("a") == 1);
    REQUIRE(longest_palindrome_substring("abcba") == 5);
    REQUIRE(longest_palindrome_substring("12345abcba6789") == 5);
}

TEST_CASE("check if is palindrome", "[palindrome]")
{
    REQUIRE(is_palindrome("dupa") == false);
    REQUIRE(is_palindrome("a") == true);
    REQUIRE(is_palindrome("aa") == true);
    REQUIRE(is_palindrome("aaa") == true);
    REQUIRE(is_palindrome("abcdcba") == true);
}
