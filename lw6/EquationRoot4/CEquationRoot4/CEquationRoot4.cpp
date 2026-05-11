#include "CEquationRoot4.h"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <cmath>


namespace
{
	bool IsCoefficientZero(double x)
	{
		return std::abs(x) < std::numeric_limits<double>::epsilon();
	}

	double CbrtSigned(double x)
	{
		return std::copysign(std::cbrt(std::abs(x)), x);
	}

	double MaxRoot3(double a, double b, double c, double d)
	{
		auto p = b / a;
		auto q = c / a;
		auto r = d / a;

		auto P = q - (p * p / 3);
		auto Q = r - (p * q / 3) + (2 * p * p * p / 27);

		auto D = (Q * Q / 4) + (P * P * P / 27);

		double t = 0.0;
		if (D > 0)
		{
			auto sqrtD = std::sqrt(D);
			t = CbrtSigned(-Q / 2 + sqrtD) + CbrtSigned(-Q / 2 - sqrtD);
		}
		else if (IsCoefficientZero(D))
		{
			double u = CbrtSigned(-Q / 2);
			t = std::max(2.0 * u, -u);
		}
		else
		{
			double sqrtTerm = 2.0 * std::sqrt(-P / 3);
			double cosArg = (Q * 3) / (P * 2) * std::sqrt(-3 / P);
			double phi = std::acos(std::clamp(cosArg, -1.0, 1.0));
			t = sqrtTerm * std::cos(phi / 3);
			t = std::max(t, sqrtTerm * std::cos((phi - 2 * M_PI) / 3.0));
			t = std::max(t, sqrtTerm * std::cos((phi - 4 * M_PI) / 3.0));
		}

		t -= p / 3;
		return t;
	}

	EquationRoot4 BiSquaredEquationRoot4(double P, double R, double p)
	{
		double D = P * P - 4 * R;
		if (D < 0)
		{
			throw std::domain_error("no all roots are real");
		}
		EquationRoot4 equation{};
		double sqrtD = std::sqrt(D);
		double signs[] = {1.0, -1.0};
		size_t numRoots = 0;
		for (const auto &x : signs)
		{
			double u = (-P + x * sqrtD) / 2;
			if (u >= 0)
			{
				double sqrtU = std::sqrt(u);
				equation.roots[numRoots] = sqrtU - (p / 4);
				numRoots++;
				if (!IsCoefficientZero(sqrtU))
				{
					equation.roots[numRoots] = -sqrtU - (p / 4);
					numRoots++;
				}
			}
		}
		equation.numRoots = numRoots;
		return equation;
	}

}

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (IsCoefficientZero(a))
	{
		throw std::invalid_argument("first coefficient must be not zero");
	}
	auto p = b / a;
	auto q = c / a;
	auto r = d / a;
	auto s = e / a;

	auto P = q - (3 * p * p / 8);
	auto Q = r - (p * q / 2) + (p * p * p / 8);
	auto R = s - (p * r / 4) + (p * p * q / 16) - (3 * p * p * p * p / 256);

	if (IsCoefficientZero(Q))
	{
		return BiSquaredEquationRoot4(P, R, p);
	}

	double a3 = 1.0;
	double b3 = P * 2;
	double c3 = P * P - 4 * R;
	double d3 = -(Q * Q);

	auto m0 = MaxRoot3(a3, b3, c3, d3);

	if  (m0 <= 0)
	{
		return {};
	}

	auto alpha = std::sqrt(m0);
	auto betaHalf = (P + m0) / 2;
	auto beta2Half = Q / (2 * alpha);

	double D1 = m0 - 4 * (betaHalf - beta2Half);
	double D2 = m0 - 4 * (betaHalf + beta2Half);
	if (D1 < 0 || D2 < 0)
	{
		throw std::domain_error("no all roots are real");
	}

	double sqrtD1 = std::sqrt(D1);
	double sqrtD2 = std::sqrt(D2);

	EquationRoot4 equation{};
	equation.numRoots = 4;
	equation.roots[0] = (-alpha + sqrtD1) / 2 - (p / 4);
	equation.roots[1] = (-alpha - sqrtD1) / 2 - (p / 4);
	equation.roots[2] = (alpha + sqrtD2) / 2 - (p / 4);
	equation.roots[3] = (alpha - sqrtD2) / 2 - (p / 4);

	return equation;
}