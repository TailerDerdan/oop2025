#include <iostream>
#include "DictionaryModule.h"

int main(int argc, char* argv[])
{
	Args args;
	try
	{
		args = ParseArgs(argc, argv);
	}
	catch (const std::exception& exp)
	{
		std::cout << exp.what() << std::endl;
	}

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HandleDictionary(std::cin, std::cout, args.dictionaryFilePath);

	return EXIT_SUCCESS;
}