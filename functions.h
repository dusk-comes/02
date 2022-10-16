#include <vector>
#include <string>

using Ip = std::vector<std::string>;
using Pool = std::vector<Ip>;

namespace my_lib
{
    Ip split(const std::string &str, char d);

    void print_helper(const Ip &ip);

    template <typename Iter>
    void print(Iter first, Iter last);

    template <typename Iter>
    void sort(Iter first, Iter last);

    template <typename Iter, typename T>
    std::pair<Iter, Iter> filter_helper(Iter first, Iter last, const T &octet, const int &pos);

    void filter(const Pool &pool, int octet1, int octet2 = -1);
    
    void filter_any(const Pool &pool, int octet);
}

void print(Pool ips);
