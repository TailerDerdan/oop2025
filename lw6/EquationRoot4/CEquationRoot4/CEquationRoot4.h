#pragma once
#include <cmath>

struct EquationRoot4
{
	size_t numRoots = 0;
	double roots[4]{};
};

EquationRoot4 Solve4(double a, double b, double c, double d, double e);