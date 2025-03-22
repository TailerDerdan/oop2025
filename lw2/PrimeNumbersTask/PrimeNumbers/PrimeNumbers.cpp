#include "PrimeNumberFunc.h"
#include <optional>
#include <string>

struct Args
{
	std::string upperBound;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count" << std::endl
				  << "Usage: primenumber.exe <upperBound>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.upperBound = argv[1];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	const int UPPER_BOUND = stoi(args->upperBound);

	auto primeNumber = GeneratePrimeNumbersSet(UPPER_BOUND);

	std::cout << primeNumber.value().size() << std::endl;

	return 0;
}
