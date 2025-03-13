#include "PrimeNumberFunc.h"
#include <algorithm>
#include <iterator>
#include <vector>

void MarkPrimeNumbers(std::vector<bool>& isCompound, int upperBound)
{
	for (int num = LOWER_BOUND; num <= std::ceil(std::sqrt(upperBound)) + 1; ++num)
	{
		size_t primeNum = num + num;
		while (primeNum < upperBound)
		{
			isCompound[primeNum] = true;
			primeNum += num;
		}
	}
}

std::set<int> FillSet(std::vector<bool>& isCompound, int upperBound)
{
	std::set<int> result;
	for (int num = LOWER_BOUND; num < upperBound; ++num)
	{
		if (!isCompound[num])
		{
			result.insert(num);
		}
	}
	return result;
}

std::optional<std::set<int>> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < LOWER_BOUND)
	{
		return std::nullopt;
	}

	std::set<int> result;
	if (upperBound == LOWER_BOUND)
	{
		result.insert(upperBound);
		return result;
	}
	std::vector<bool> isCompound = std::vector<bool>(upperBound, false);
	MarkPrimeNumbers(isCompound, upperBound);
	result = FillSet(isCompound, upperBound);
	return result;
}