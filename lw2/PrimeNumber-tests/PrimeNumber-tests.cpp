#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../PrimeNumbers/PrimeNumberFunc.h"

TEST_CASE("Checking for finding prime numbers")
{
	auto primeNums = GeneratePrimeNumbersSet(100);
	std::set<int> result = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	CHECK(primeNums.value() == result);
}

#ifdef NDEBUG
TEST_CASE("Check count of elements in set of prime numbers")
{
	auto primeNums = TheSieveOfEratosfen(100000000);
	CHECK(primeNums.value().size() == 5761455);
}
#endif

TEST_CASE("Check lower bound")
{
	auto primeNums = GeneratePrimeNumbersSet(2);
	CHECK(primeNums.value().size() == 1);
}

TEST_CASE("Uncorrect input dates")
{
	auto primeNums = GeneratePrimeNumbersSet(-1);
	CHECK(primeNums == std::nullopt);
}