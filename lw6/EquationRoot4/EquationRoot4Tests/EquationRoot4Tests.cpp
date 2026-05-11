#include <catch2/catch_test_macros.hpp>
#include "CEquationRoot4.h"

TEST_CASE("a=0")
{
	// x^3 + x^2 + x + 1 = 0
	// not 4 roots
	CHECK_THROWS_AS(Solve4(0, 1, 1, 1, 1), std::invalid_argument);
}

TEST_CASE("no real roots")
{
	// x^4 + 4x^2 + 5 = 0
	// D = 16 - 20 < 0
	CHECK_THROWS_AS(Solve4(1, 0, 4, 0, 5), std::domain_error);

	// (x - 1)(x - 2)(x^2 + 2x + 2) = 0
	// third () has complex roots
	CHECK_THROWS_AS(Solve4(1, -1, -2, -2, 4), std::domain_error);
}

TEST_CASE("be squared equation")
{
	// x^4 - 5x^2 + 4 = 0
	auto roots = Solve4(1, 0, -5, 0, 4);
	CHECK(roots.numRoots == 4);
	CHECK(roots.roots[0] == 2.0);
	CHECK(roots.roots[1] == -2.0);
	CHECK(roots.roots[2] == 1.0);
	CHECK(roots.roots[3] == -1.0);
}

TEST_CASE("4 real roots")
{
	// (x - 1)(x - 2)(x - 3)(x - 4) = 0
	auto roots = Solve4(1, -10, 35, -50, 24);
	CHECK(roots.numRoots == 4);
	CHECK(roots.roots[0] == 4.0);
	CHECK(roots.roots[1] == 1.0);
	CHECK(roots.roots[2] == 3.0);
	CHECK(roots.roots[3] == 2.0);
}