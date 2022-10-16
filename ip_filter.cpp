#include <iostream>
#include <string>
#include <vector>
#include "functions.h"

using Ip = std::vector<std::string>;
using Pool = std::vector<Ip>;

int main(int argc, char const *argv[])
{
    try
    {
        Pool ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            Ip ip = my_lib::split(line, '\t');
            ip_pool.push_back(my_lib::split(ip.at(0), '.'));
        }

        my_lib::sort(ip_pool.begin(), ip_pool.end());

        my_lib::print(ip_pool.cbegin(), ip_pool.cend());

        my_lib::filter(ip_pool, 1);

        my_lib::filter(ip_pool, 46, 70);

        my_lib::filter_any(ip_pool, 46);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
