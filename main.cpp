#define CATCH_CONFIG_MAIN
#include "externals/catch.hpp"

#include "longest_palindrome_substring.hpp"

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
