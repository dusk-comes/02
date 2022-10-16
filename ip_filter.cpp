#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>

using Ip = std::vector<std::string>;
using Pool = std::vector<Ip>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

namespace my
{
    Ip split(const std::string &str, char d)
    {
        Ip r;
    
        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while(stop != std::string::npos)
        {
            r.push_back(str.substr(start, stop - start));
    
            start = stop + 1;
            stop = str.find_first_of(d, start);
        }
    
        r.push_back(str.substr(start));
    
        return r;
    }

    void print_helper(const Ip &ip)
    {
        std::copy(ip.begin(), ip.end()-1, std::ostream_iterator<Ip::value_type>(std::cout, "."));
        std::copy(ip.end()-1, ip.end(), std::ostream_iterator<Ip::value_type>(std::cout));
        std::cout << std::endl;
    }

    template <typename Iter>
    void print(Iter first, Iter last)
    {
    
        std::for_each(first, last, print_helper);
    }

    template <typename Iter>
    void sort(Iter first, Iter last)
    {
        std::sort(first, last, [](const auto& ip_a, const auto& ip_b)
                {
                    for (auto octet_a = ip_a.cbegin(), octet_b = ip_b.cbegin(); octet_a != ip_a.cend() || octet_b != ip_b.cend(); ++octet_a, ++octet_b)
                    {
                        if (octet_a->size() < octet_b->size()) return false;
                        else if (octet_a->size() > octet_b->size()) return true;
                        else
                        {
                            for (auto chr_a = octet_a->cbegin(), chr_b = octet_b->cbegin(); chr_a != octet_a->cend(); ++chr_a, ++chr_b)
                            {
                                if (*chr_a < *chr_b) return false;
                                else if (*chr_a > *chr_b) return true;
                            }
                        }
                    }
                    return false;
                });
    }

    template <typename Iter, typename T>
    std::pair<Iter, Iter> filter_helper(Iter first, Iter last, const T &octet, const int &pos)
    {
        auto ip_begin = std::lower_bound(first, last, octet, [pos](const auto& ip, const auto& value) {
              return std::stoi(ip.at(pos)) > value;});
    
        auto ip_end = std::upper_bound(first, last, octet, [pos](const auto& value, const auto& ip) {
                    return std::stoi(ip.at(pos)) < value;});
    
        return {ip_begin, ip_end};
    }
    
    void filter(const Pool &pool, int octet1, int octet2 = -1)
    {
        auto bounds = filter_helper(pool.cbegin(), pool.cend(), octet1, 0);
    
        if (octet2 != -1)
        {
            bounds = filter_helper(bounds.first, bounds.second, octet2, 1);
        }
    
        print(bounds.first, bounds.second);
    }

    void filter_any(const Pool &pool, int octet)
    {
        auto _print = [octet](const auto &ip)
        {
            if (std::find(ip.cbegin(), ip.cend(), std::to_string(octet)) != ip.cend())
            {
               print_helper(ip);
            }
        };

        std::for_each(pool.cbegin(), pool.cend(), _print);
    }
}



int main(int argc, char const *argv[])
{
    try
    {
        Pool ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            Ip ip = my::split(line, '\t');
            ip_pool.push_back(my::split(ip.at(0), '.'));
        }

        my::sort(ip_pool.begin(), ip_pool.end());

        my::print(ip_pool.cbegin(), ip_pool.cend());

        my::filter(ip_pool, 1);

        my::filter(ip_pool, 46, 70);

        my::filter_any(ip_pool, 46);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
