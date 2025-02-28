#include <iostream>
#include <optional>
#include <fstream>
#include <string>

struct Args
{
	std::string idCrypt;
	std::string input;
	std::string output;
	std::string key;
};

namespace
{
	const int RADIX_10 = 10;

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

	uint32_t GetBit(int& x, int p)
	{
		return (x >> p) & ~(~0 << 1);
	}

	uint32_t MoveBit(uint32_t& x, int n)
	{
		return (x << n);
	}

	int MixBit(int x)
	{
		uint32_t temp = GetBit(x, 7);
		uint32_t result = 0;
		result = result | MoveBit(temp, 5);
		temp = GetBit(x, 6);
		result = result | MoveBit(temp, 1);
		temp = GetBit(x, 5);
		result = result | MoveBit(temp, 0);
		temp = GetBit(x, 4);
		result = result | MoveBit(temp, 7);
		temp = GetBit(x, 3);
		result = result | MoveBit(temp, 6);
		temp = GetBit(x, 2);
		result = result | MoveBit(temp, 4);
		temp = GetBit(x, 1);
		result = result | MoveBit(temp, 3);
		temp = GetBit(x, 0);
		result = result | MoveBit(temp, 2);
		return result;
	}

	void Encryption(std::ifstream& input, std::ofstream& output, int key)
	{
		char ch;
		int chNum = 0;
		while (input.get(ch))
		{
			chNum = int(ch);
			int result = chNum ^ key;
			result = MixBit(result);
			output.put(char(result));
		}
	}

	int ReverseMixBit(int x)
	{
		uint32_t temp = GetBit(x, 7);
		uint32_t result = 0;
		result = result | MoveBit(temp, 4);
		temp = GetBit(x, 6);
		result = result | MoveBit(temp, 3);
		temp = GetBit(x, 5);
		result = result | MoveBit(temp, 7);
		temp = GetBit(x, 4);
		result = result | MoveBit(temp, 2);
		temp = GetBit(x, 3);
		result = result | MoveBit(temp, 1);
		temp = GetBit(x, 2);
		result = result | MoveBit(temp, 0);
		temp = GetBit(x, 1);
		result = result | MoveBit(temp, 6);
		temp = GetBit(x, 0);
		result = result | MoveBit(temp, 5);
		return result;
	}

	void DeEncryption(std::ifstream& input, std::ofstream& output, int key)
	{
		char ch;
		int chNum = 0;
		while (input.get(ch))
		{
			chNum = int(ch);
			int result = ReverseMixBit(chNum);
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
		if (!keyInt || keyInt.value() > 255)
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
			DeEncryption(inputFile, outputFile, keyInt.value());
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