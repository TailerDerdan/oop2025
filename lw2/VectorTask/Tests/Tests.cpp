#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Vector_task2/HandleVector.h"

TEST_CASE("Multiply elements of empty vector given empty vector")
{
	std::vector<double> vector;
	MultiplyByMinElement(vector);
	REQUIRE(vector.empty());
}

TEST_CASE("Multiplay all elements of vector on min element")
{
	std::vector<double> vector = { -6, 5, 3.345, 7, 6, 2 };
	std::vector<double> correctVector = { 36, -30, -20.07, -42, -36, -12 };
	MultiplyByMinElement(vector);
	REQUIRE(vector == correctVector);
}