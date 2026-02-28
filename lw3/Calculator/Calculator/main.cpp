#include <iostream>

#include "CalculatorUI.h"

int main()
{
    Calculator calculator;
    CalculatorUI calculatorUI(std::cin, std::cout, calculator);

    std::cout << ">";
    while (true)
    {
        calculatorUI.HandleCommand();
        std::cout << ">";
    }
}