#include <vector>
#include <array>
#include <string>

using Ip = std::array<int, 4>;
using Pool = std::vector<Ip>;

namespace my_lib
{
    void print_helper(const Ip &ip);

    template <typename Iter>
    void print(Iter first, Iter last);

    template <typename Iter, typename T>
    std::pair<Iter, Iter> filter_helper(Iter first, Iter last, const T &octet, const int &pos);

    template <typename Iter>
    void filter(Iter first, Iter last, int octet1, int octet2 = -1);
    
    template <typename Iter>
    void filter_any(Iter first, Iter last, int octet);
}
