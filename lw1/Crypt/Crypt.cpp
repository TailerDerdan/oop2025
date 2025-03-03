#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <map>

//переделать структуру под значения, которые мы используем
struct Args
{
	std::string idCrypt;
	std::string input;
	std::string output;
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
	std::optional<int> StringToInt(const std::string& str)
	{
		int i = 0;
		int result = 0;
		std::optional<int> charNumber = 0;

		while (i <= str.length() - 1)
		{
			charNumber = LetterToNumber(str[i]);
			if ((!charNumber) || (charNumber.value() > RADIX_10))
			{
				return std::nullopt;
			}
			if (result > ((INT32_MAX - charNumber.value()) / RADIX_10))
			{
				return std::nullopt;
			}
			result = result * RADIX_10 + charNumber.value();
			i++;
		}
		return result;
	}
	// разобраться с передачей по ссылке
	uint32_t GetBit(int& num, int numberOfBit)
	{
		return (num >> numberOfBit) & ~(~0 << 1);
	}
	//разобраться с передачей по ссылке
	uint32_t MoveBit(uint32_t& num, int numberOfBit)
	{
		return (num << numberOfBit);
	}
	//переименовать в mixbits
	int MixBit(int num)
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
	void Encryption(std::ifstream& input, std::ofstream& output, int key)
	{
		char ch;
		//убрать chNum
		while (input.get(ch))
		{
			int result = ch ^ key;
			result = MixBit(result);
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
	void Deencryption(std::ifstream& input, std::ofstream& output, int key)
	{
		char ch;
		while (input.get(ch))
		{
			int result = ReverseMixBit(ch);
			result = result ^ key;
			output.put(char(result));
		}
	}

	std::optional<Args> ParseArgs(int argc, char* argv[])
	{
		if (argc != 5)
		{
			std::cout << "Invalid argument count" << std::endl
				<< "Usage: crypt.exe <inputFile> <outputFile> <crypt> <key>" << std::endl;
			return std::nullopt;
		}
		Args args;
		args.input = argv[1];
		args.output = argv[2];
		args.idCrypt = argv[3];
		args.key = argv[4];
		return args;
	}

	void PrintError()
	{
		std::cout << "Incorrect data entry.\n";
		std::cout << "Please enter numbers or letter(A..Z)\n";
	}

	bool CryptOrDecryptFile(const Args& args)
	{
		std::ifstream inputFile(args.input, std::ios::binary);
		std::ofstream outputFile(args.output, std::ios::binary);

		if (!inputFile.is_open())
		{
			std::cout << "Failed to open '" << args.input << "' for reading\n";
			return false;
		}

		if (!outputFile.is_open())
		{
			std::cout << "Failed to open '" << args.output << "' for writing\n";
			return false;
		}

		auto keyInt = StringToInt(args.key);
		if (!keyInt || keyInt.value() > MAX_KEY)
		{
			PrintError();
			return false;
		}

		if (args.idCrypt == "crypt")
		{
			Encryption(inputFile, outputFile, keyInt.value());
		}
		else if (args.idCrypt == "decrypt")
		{
			Deencryption(inputFile, outputFile, keyInt.value());
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
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	if (!CryptOrDecryptFile(args.value()))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}