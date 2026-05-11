#include <iostream>
#include "CEquationRoot4.h"

int main()
{
	double a, b, c, d, e;
	std::cout << "Enter coefficients for equation 4: a b c d e: " << std::endl;
	if (std::cin >> a >> b >> c >> d >> e)
	{
		try
		{
			auto roots = Solve4(a, b, c, d, e);
			std::cout << std::endl << "Roots: " << std::endl;
			for (size_t iter = 0; iter < roots.numRoots; iter++)
			{
				std::cout << roots.roots[iter] << std::endl;
			}
		}
		catch (const std::exception& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}
	return EXIT_FAILURE;
}