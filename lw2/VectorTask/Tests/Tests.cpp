#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Vector_task2/HandleVector.h"

TEST_CASE("Multiply elements of empty vector given empty vector")
{
	std::vector<double> vector;
	MultiplyByMinElement(vector);
	CHECK(vector.empty());
}

//добавить еще тестов
TEST_CASE("Multiplay all elements of vector on min element")
{
	std::vector<double> vector = { -6, 5, 3.345, 7, 6, 2 };
	std::vector<double> correctVector = { 36, -30, -20.07, -42, -36, -12 };
	MultiplyByMinElement(vector);
	CHECK(vector == correctVector);
}

TEST_CASE("Sort element")
{
	std::vector<double> vec = { 3.43, 10, 0, -9, 3.44, 5 };
	std::vector<double> result = { -9, 0, 3.43, 3.44, 5, 10 };
	SortVector(vec);
	CHECK(result == vec);
}

TEST_CASE("Print elements of vector")
{
	std::vector<double> vec = { 3.43, 10, 0, -9, 3.44, 5 };
	std::ostringstream oss;
	std::string result = "-9.000, 0.000, 3.430, 3.440, 5.000, 10.000";
	PrintSortedVector(vec, oss);
	CHECK(oss.str() == result);
}
//добавить тесты на сортировку и на print