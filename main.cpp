#include <iostream>
#include <iterator>
#include <string>

#define CATCH_CONFIG_MAIN
#include "externals/catch.hpp"

auto to_forward_it(const auto reverse_it) {
    return std::next(reverse_it.base());
//    return reverse_it.base();
}

bool is_palindrome(const std::string& s) {
    auto begin = s.begin();
    auto end = s.rbegin();
    while (begin != s.end() and end != s.rend()){
        if (*begin != *end){
            return false;
        }
        std::advance(begin, 1);
        std::advance(end, 1);
        // fixme: could stop in the middle
    }
    return true;
}

unsigned longest_palindrome_substring(const std::string& input) {
    std::size_t benchmark = input.empty() ? 0 : 1;
    auto center = input.begin();
    while (center != input.end()) {
        auto left = center;
        auto right = std::next(center);
        do {
            std::advance(left, -1);
            std::advance(right, 1);
            std::string candidate_odd(left, right);
            std::string candidate_even(left-1, right);
            if (is_palindrome(candidate_odd)) {
                benchmark = std::max(benchmark, candidate_odd.length());
            }
            else if (is_palindrome(candidate_even)) {
                benchmark = std::max(benchmark, candidate_even.length());
            }
            else {
                break;
            }
        }
        while (std::reverse_iterator(left) != input.rend() && right != input.end());

        std::advance(center, 1);
    }
    return benchmark;
}

TEST_CASE("found longest palindrome", "[palindrome]") {
    REQUIRE(longest_palindrome_substring("") == 0);
//    REQUIRE(longest_palindrome_substring("a") == 1);
    REQUIRE(longest_palindrome_substring("abcba") == 5);
    REQUIRE(longest_palindrome_substring("abba") == 4);
    REQUIRE(longest_palindrome_substring("aa") == 2);
    REQUIRE(longest_palindrome_substring("12345abcba6789") == 6);
}

TEST_CASE("check if is palindrome", "[palindrome]")
{
    REQUIRE(is_palindrome("dupa") == false);
    REQUIRE(is_palindrome("a") == true);
    REQUIRE(is_palindrome("aa") == true);
    REQUIRE(is_palindrome("aaa") == true);
    REQUIRE(is_palindrome("abcdcba") == true);
}
