#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>

//переделать структуру под значения, которые мы используем
struct FilePaths
{
	std::string input;
	std::string output;
};

struct PropertiesCrypting
{
	std::string idCrypt;
	std::string key;
};

//поправить тест с exe файлом
namespace
{
	const int RADIX_10 = 10;
	const int MAX_KEY = 255;

	std::optional<int> LetterToNumber(char ch)
	{
		const int DIF_BETW_NUMBER_OF_DIGIT_AND_LETTER = 7;
		const char CONST_FOR_CONVERT_CHAR_TO_DIGIT = '0';
		if (isdigit(ch))
		{
			return ch - CONST_FOR_CONVERT_CHAR_TO_DIGIT;
		}
		if (isalpha(ch))
		{
			return ch - CONST_FOR_CONVERT_CHAR_TO_DIGIT - DIF_BETW_NUMBER_OF_DIGIT_AND_LETTER;
		}
		return std::nullopt;
	}

	//заменить на stoi
	// разобраться с передачей по ссылке
	uint32_t GetBit(int num, int numberOfBit)
	{
		return (num >> numberOfBit) & ~(~0 << 1);
	}
	//разобраться с передачей по ссылке
	uint32_t MoveBit(uint32_t num, int numberOfBit)
	{
		return (num << numberOfBit);
	}
	//переименовать в mixbits
	int MixBits(int num)
	{
		std::map<int, int> newPlaceOfBit = {
			{ 7, 5 },
			{ 6, 1 },
			{ 5, 0 },
			{ 4, 7 },
			{ 3, 6 },
			{ 2, 4 },
			{ 1, 3 },
			{ 0, 2 },
		};

		uint32_t result = 0;
		for (int iter = 0; iter < 8; iter++)
		{
			uint32_t temp = GetBit(num, newPlaceOfBit.find(iter)->first);
			result = result | MoveBit(temp, newPlaceOfBit.find(iter)->second);
		}
		return result;
	}
	//переименовать в encrypt
	void Encrypt(std::ifstream& input, std::ofstream& output, int key)
	{
		char ch;
		//убрать chNum
		while (input.get(ch))
		{
			int result = ch ^ key;
			result = MixBits(result);
			output.put(char(result));
		}
	}

	int ReverseMixBit(int num)
	{
		std::map<int, int> newPlaceOfBit = {
			{ 7, 4 },
			{ 6, 3 },
			{ 5, 7 },
			{ 4, 2 },
			{ 3, 1 },
			{ 2, 0 },
			{ 1, 6 },
			{ 0, 5 },
		};

		uint32_t result = 0;
		for (int iter = 0; iter < 8; iter++)
		{
			uint32_t temp = GetBit(num, newPlaceOfBit.find(iter)->first);
			result = result | MoveBit(temp, newPlaceOfBit.find(iter)->second);
		}
		return result;
	}
	// переименовать в deencrypt
	void Deencrypt(std::ifstream& input, std::ofstream& output, int key)
	{
		char ch;
		while (input.get(ch))
		{
			int result = ReverseMixBit(ch);
			result = result ^ key;
			output.put(char(result));
		}
	}

	void ParseArgs(int argc, char* argv[], FilePaths& paths, PropertiesCrypting& properties)
	{
		if (argc != 5)
		{
			throw std::invalid_argument("Invalid argument count\nUsage: crypt.exe <inputFile> <outputFile> <crypt> <key>");
		}
		paths.input = argv[1];
		paths.output = argv[2];
		properties.idCrypt = argv[3];
		properties.key = argv[4];
	}

	void PrintError()
	{
		std::cout << "Incorrect data entry.\n";
		std::cout << "Please enter numbers or letter(A..Z)\n";
	}

	bool CryptOrDecryptFile(const FilePaths& paths, const PropertiesCrypting& properties)
	{
		std::ifstream inputFile(paths.input, std::ios::binary);
		std::ofstream outputFile(paths.output, std::ios::binary);

		if (!inputFile.is_open())
		{
			std::cout << "Failed to open '" << paths.input << "' for reading\n";
			return false;
		}

		if (!outputFile.is_open())
		{
			std::cout << "Failed to open '" << paths.output << "' for writing\n";
			return false;
		}
		int keyInt = 0;
		try
		{
			keyInt = std::stoi(properties.key);
		}
		catch (const std::exception& exp)
		{
			std::cout << exp.what() << std::endl;
			return false;
		}
		
		if (keyInt > MAX_KEY)
		{
			PrintError();
			return false;
		}

		if (properties.idCrypt == "crypt")
		{
			Encrypt(inputFile, outputFile, keyInt);
		}
		else if (properties.idCrypt == "decrypt")
		{
			Deencrypt(inputFile, outputFile, keyInt);
		}
		else
		{
			std::cout << "Enter crypt or decrypt please" << std::endl;
			return false;
		}
		return true;
	}
}

int main(int argc, char* argv[])
{
	FilePaths paths;
	PropertiesCrypting properties;
	try
	{
		ParseArgs(argc, argv, paths, properties);
	}
	catch (const std::exception& exp)
	{
		std::cout << exp.what() << std::endl;
		return EXIT_FAILURE;
	}

	if (!CryptOrDecryptFile(paths, properties))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}