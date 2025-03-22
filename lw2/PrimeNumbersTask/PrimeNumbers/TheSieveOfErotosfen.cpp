#include "PrimeNumberFunc.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

const int LOWER_BOUND = 2;
const int UPPER_BOUND = 100000000;
//добавить верхнюю границу

void MarkPrimeNumbers(std::vector<bool>& isCompound, int upperBound)
{
	//сделать алгоритм быстрее в 2 раза
	int num = LOWER_BOUND;
	while (num * num <= upperBound)
	{
		size_t primeNum = num + num;
		if (primeNum % 2 != 0 && !isCompound[primeNum])
		{
			while (primeNum <= upperBound)
			{
				isCompound[primeNum] = true;
				primeNum += num;
			}
		}
		num++;
	}
}

std::set<int> FillSet(std::vector<bool>& isCompound, int upperBound)
{
	std::set<int> result;
	for (int num = LOWER_BOUND; num <= upperBound; ++num)
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
	if (upperBound < LOWER_BOUND || upperBound > UPPER_BOUND)
	{
		return std::nullopt;
	}

	std::set<int> result;
	if (upperBound == LOWER_BOUND)
	{
		result.insert(upperBound);
		return result;
	}
	std::vector<bool> isCompound = std::vector<bool>(upperBound + 1, true);
	MarkPrimeNumbers(isCompound, upperBound);
	result = FillSet(isCompound, upperBound);
	return result;
}