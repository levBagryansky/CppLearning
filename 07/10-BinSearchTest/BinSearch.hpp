#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>

auto find(const int * array, std::size_t size, int key)
{
    auto result = false;

    if (size > 0)
    {
        auto l = 0uz, r = size - 1, m = 0uz;

        while (l < r)
        {
            array[m = std::midpoint(l, r)] < key ? l = m + 1 : r = m;
        }

        result = array[l] == key;
    }

    return result;
}
