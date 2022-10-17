#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include "functions.h"

int main(int argc, char const *argv[])
{
    try
    {
        Pool ip_pool;
        ip_pool.reserve(1000);

        for(std::string value; std::getline(std::cin, value, '\t');)
        {
            std::istringstream is(value);
            std::array<int, 4> ip{0, 0, 0, 0};
            int i = 0;
            for(std::string octet; std::getline(is, octet, '.'); ++i)
            {
                ip.at(i) = std::stoi(octet);
            }
            ip_pool.push_back(ip);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }

        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::array<int, 4>>());

        my_lib::print(ip_pool.cbegin(), ip_pool.cend());

        my_lib::filter(ip_pool.cbegin(), ip_pool.cend(), 1);

        my_lib::filter(ip_pool.cbegin(), ip_pool.cend(), 46, 70);

        my_lib::filter_any(ip_pool.cbegin(), ip_pool.cend(), 46);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << " at " << __LINE__ << std::endl;
    }

    return 0;
}
