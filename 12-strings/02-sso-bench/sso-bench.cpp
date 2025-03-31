#include <exception>
#include <benchmark/benchmark.h>

void test(benchmark::State &state)
{
    int Len = state.range(0);
    for (auto _ : state)
    {
        std::string mystring(Len - 1, 'A'); // '\0' also
        benchmark::DoNotOptimize(mystring);
    }
}

BENCHMARK(test)->DenseRange(3, 20)
    ->Args({30})
    ->Args({60})
    ->Args({120})
    ->Args({240})
    ->Args({480})
    ->Args({1000});

BENCHMARK_MAIN();