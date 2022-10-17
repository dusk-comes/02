#include "functions.h"
#include <iterator>
#include <iostream>
#include <algorithm>
#include <ostream>

namespace my_lib
{
    void print_helper(const Ip &ip)
    {
        std::copy(ip.cbegin(), ip.cend()-1, std::ostream_iterator<Ip::value_type>(std::cout, "."));
        std::copy(ip.cend()-1, ip.cend(), std::ostream_iterator<Ip::value_type>(std::cout));
        std::cout << std::endl;
    }

    template <typename Iter>
    void print(Iter first, Iter last)
    {
    
        std::for_each(first, last, print_helper);
    }

    template <typename Iter, typename T>
    std::pair<Iter, Iter> filter_helper(Iter first, Iter last, const T &octet, const int &pos)
    {
        auto ip_begin = std::lower_bound(first, last, octet, [pos](const auto& ip, const auto& value) {
              return ip.at(pos) > value;});
    
        auto ip_end = std::upper_bound(first, last, octet, [pos](const auto& value, const auto& ip) {
                    return ip.at(pos) < value;});
    
        return {ip_begin, ip_end};
    }

    template <typename Iter>
    void filter(Iter first, Iter last, int octet1, int octet2)
    {
        auto bounds = filter_helper(first, last, octet1, 0);
    
        if (octet2 != -1)
        {
            bounds = filter_helper(bounds.first, bounds.second, octet2, 1);
        }
    
        print(bounds.first, bounds.second);
    }

    template <typename Iter>
    void filter_any(Iter first, Iter last, int octet)
    {
        auto _print = [octet](const auto &ip)
        {
            if (std::find(ip.cbegin(), ip.cend(), octet) != ip.cend())
            {
               print_helper(ip);
            }
        };

        std::for_each(first, last, _print);
    }
}

template void my_lib::filter<Pool::const_iterator>(Pool::const_iterator, Pool::const_iterator, int, int);
template void my_lib::filter_any<Pool::const_iterator>(Pool::const_iterator, Pool::const_iterator, int);
