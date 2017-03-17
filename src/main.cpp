#include "../area51/random_engine.hpp"
#include "../area51/benchmark_v2.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <random>

template<typename It>
It partition(It begin, It end, It pivot)
{
    std::swap(*begin, *pivot);
    pivot = begin;
    It i{ begin }, j = std::next(begin, 1);
    for(;j != end; j++)
    {
        if(*j < *pivot)
            std::swap(*j, *++i);
    }
    std::swap(*pivot, *i);
    return i;
}

template<typename It>
void quick_sort(It begin, It end)
{
    if (std::distance(begin, end) == 0)
        return;
    It pivot{ begin };
    It elementAtCorrectPosition = partition(begin, end, pivot);
    quick_sort(begin, elementAtCorrectPosition);
    quick_sort(std::next(elementAtCorrectPosition, 1), end);
}

class generator
{
    shino::random_int_generator<int, std::mt19937_64> gen;
public:
    using input_type = std::size_t;
    
    std::tuple<std::vector<int>> operator()(input_type size)
    {
        static std::vector<int> v;
        if (v.size() == size)
        {
            return v;
            
        }
        v.resize(size);
        gen(v.begin(), v.end());
        
        return v;
    }
};

int main()
{
    auto standard_sort = [](std::vector<int>& v)
    {
        std::sort(v.begin(), v.end());
    };
    auto user_quicksort = [](std::vector<int>& v)
    {
        quick_sort(v.begin(), v.end());
    };
    
    auto bench = shino::benchmarker(generator{}, standard_sort, user_quicksort);
    
    for (std::size_t i = 100; i <= 100'000; i += 100)
    {
        bench.time(i, 5);
    }
    
    std::string dir = "../benchmarks/";
    bench.save_as<std::chrono::microseconds>(dir + "benchmarks.txt",
                  {dir + "standard sort timings.txt", dir + "quicksort timings.txt"},
                  "Array size", "Milliseconds");
}