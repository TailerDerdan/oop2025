#include <iostream>
#include "CDate.h"

int main()
{
    CDate data;
    std::cin >> data;
    std::cout << "--------------" << std::endl;
    std::cout << data << std::endl;

    CDate data2;
    std::cin >> data2;
    std::cout << "--------------" << std::endl;
    std::cout << data2 << std::endl;

    std::cout << data - data2 << std::endl;
    std::cout << data + 10 << std::endl;
    std::cout << "--------------" << std::endl;

    std::cout << data++ << std::endl;
    std::cout << data2-- << std::endl;
    std::cout << "--------------" << std::endl;

    std::cout << ++data << std::endl;
    std::cout << --data2 << std::endl;
    std::cout << "--------------" << std::endl;

    data2 += 2;
    std::cout << data2 << std::endl;
    std::cout << "--------------" << std::endl;

    data2 -= 2;
    std::cout << data2 << std::endl;
    std::cout << "--------------" << std::endl;

    std::cout << (data == data2) << std::endl;
    std::cout << (data != data2) << std::endl;
    std::cout << (data < data2) << std::endl;
    std::cout << (data <= data2) << std::endl;
    std::cout << (data > data2) << std::endl;
    std::cout << (data >= data2) << std::endl;
    std::cout << "--------------" << std::endl;

    return 0;
}