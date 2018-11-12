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
    }
    return true;
}

bool update_score(std::size_t& benchmark, const auto left, const auto right)
{
    std::string candidate(left, right);
    if (is_palindrome(candidate)){
        benchmark = std::max(benchmark, candidate.length());
        return true;
    }
    return false;
}

void lookup_impl(const auto begin, const auto end, auto left, auto right, std::size_t& benchmark)
{
    do {
        if (not update_score(benchmark, left, right))
        {
            break;
        }
        std::advance(right, 1);
        std::advance(left, -1);
    }
    while(right != end and left != begin);
    update_score(benchmark, left, right);
}

std::size_t longest_even_palindrome_substring(const auto cursor, const std::string& input){
    std::size_t benchmark = 0;
    if (std::next(cursor) == input.end()){
        return benchmark;
    }

    auto left = cursor;
    auto right = std::next(cursor, 2);

    if (left == input.begin() or right == input.end()){
        update_score(benchmark, left, right);
        return benchmark;
    }

    lookup_impl(input.begin(), input.end(), left,right, benchmark);
    return benchmark;
}

std::size_t longest_odd_palindrome_substring(const auto cursor, const std::string& input){
    std::size_t benchmark = 0;
    auto left = cursor;
    if (left == input.end())
    {
        return benchmark;
    }

    auto right = std::next(cursor, 1);
    if (right == input.end()){
        return 1;
    }

    lookup_impl(input.begin(), input.end(), left,right, benchmark);
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
