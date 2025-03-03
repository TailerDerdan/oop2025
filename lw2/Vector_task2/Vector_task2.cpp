﻿#include "modules.h"

int main()
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));

	MultiplyByMinElement(numbers);
	WriteSortedVector(numbers, std::cout);

	return EXIT_SUCCESS;
}