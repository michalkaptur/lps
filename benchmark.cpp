#include <benchmark/benchmark.h>
#include "longest_palindrome_substring.hpp"


static void benchmark_lps(benchmark::State& state){
    std::string s(state.range(), 'a'); //worst case
    for (auto _ : state) {
      benchmark::DoNotOptimize(longest_palindrome_substring(s));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(benchmark_lps)
    ->RangeMultiplier(2)->Range(10, 500)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
