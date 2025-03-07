#include "HandleVector.h"

std::vector<double> ReadNumbers(std::istream& input)
{
	std::vector<double> numbers(std::istream_iterator<double>(input), (std::istream_iterator<double>()));
	return numbers;
}

int main()
{
	auto numbers = ReadNumbers(std::cin);
	MultiplyByMinElement(numbers);
	PrintSortedVector(numbers, std::cout);

	return EXIT_SUCCESS;
}