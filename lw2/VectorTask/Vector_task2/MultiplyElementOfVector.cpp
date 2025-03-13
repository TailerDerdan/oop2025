#include "HandleVector.h"

#include <algorithm>
#include <iomanip>

void MultiplyByMinElement(std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}
	const double min = *std::min_element(numbers.begin(), numbers.end());
	std::transform(numbers.begin(), numbers.end(), numbers.begin(), [min](double num) { return num * min; });
}

void SortVector(std::vector<double>& numbers)
{
	std::sort(numbers.begin(), numbers.end());
}

void PrintSortedVector(std::vector<double> numbers, std::ostream& output)
{
	if (numbers.empty())
	{
		return;
	}
	SortVector(numbers);
	output << std::setprecision(3) << std::fixed;
	copy(numbers.begin(), numbers.end() - 1, std::ostream_iterator<double>(output, ", "));
	output << *(numbers.end() - 1);
}