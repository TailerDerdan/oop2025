#include <iostream>
#include <windows.h>
#include "UI.h"

//скоректировать программу

void SaveChagesInFile(Dictionary& dictionary, std::istream& input, std::ostream& output, 
	std::fstream& dictionaryFile, const std::string& dictionaryFilePath)
{
	output << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
	char ch;
	input >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		dictionaryFile.open(dictionaryFilePath);
		PrintDicitionaryInFile(dictionary, dictionaryFile);
		output << "Изменения сохранены. До свидания." << std::endl;
	}
	else
	{
		output << "Изменения не сохранены. До свидания." << std::endl;
	}
}

bool HandleDictionary(std::istream& input, std::ostream& output, const std::string& dictionaryFilePath)
{
	Dictionary dictionary;
	std::fstream dictionaryFile;

	dictionaryFile.open(dictionaryFilePath);
	if (!dictionaryFile.is_open())
	{
		std::cout << "Failed to open '" << dictionaryFilePath << "' for reading\n";
		return false;
	}

	try
	{
		dictionary = ReadDictionaryFromFile(dictionaryFile);
	}
	catch (const std::exception& exp)
	{
		output << exp.what() << std::endl;
		return false;
	}
	dictionaryFile.close();

	bool isDictionaryChanged = false;
	WorkWithDictionary(dictionary, input, output, isDictionaryChanged);

	if (isDictionaryChanged)
	{
		SaveChagesInFile(dictionary, input, output, dictionaryFile, dictionaryFilePath);
	}
	return true;
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: Dictionary.exe <dictionary.txt>");
	}
	Args args;
	args.dictionaryFilePath = argv[1];
	return args;
}

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