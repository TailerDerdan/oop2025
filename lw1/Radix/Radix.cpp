#include <iostream>
#include <optional>
#include <string>
#include <cmath>

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

struct IncomingValues
{
	int sourceNotation = 0;
	int destinationNotation = 0;
	int value = 0;
};

namespace
{
	//переимновать в max и min
	const int MIN_RADIX = 2;
	const int MAX_RADIX = 36;
	const char NEGATIVE_CHAR = '-';

	std::optional<Args> ParseArgs(int argc, char* argv[])
	{
		std::string sourceNotation;
		std::string destinationNotation;
		std::string value;

		Args args;

		if (argc == 1)
		{
			std::getline(std::cin, sourceNotation);
			std::getline(std::cin, destinationNotation);
			std::getline(std::cin, value);

			args.sourceNotation = sourceNotation;
			args.destinationNotation = destinationNotation;
			args.value = value;
			return args;
		}
		if (argc != 4)
		{
			std::cout << "Invalid argument count" << std::endl;
			std::cout << "Usage: radix.exe <SourceNotation> <DestinationNotation> <value>" << std::endl;
			return std::nullopt;
		}
		args.sourceNotation = argv[1];
		args.destinationNotation = argv[2];
		args.value = argv[3];

		return args;
	}

	void PrintError()
	{
		std::cout << "Incorrect data entry." << std::endl;
		std::cout << "Please enter numbers or letter(A..Z)" << std::endl;
	}

	bool isRadixInBounds(int radix)
	{
		if ((radix < MIN_RADIX) || (radix > MAX_RADIX))
		{
			return false;
		}
		return true;
	}

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

	std::optional<int> StringToInt(const std::string& str, int radix)
	{
		if ((str.empty()) || !isRadixInBounds(radix))
		{
			return std::nullopt;
		}

		int i = 0;

		bool isNegative = false;

		if (str[0] == NEGATIVE_CHAR)
		{
			isNegative = true;
			i = 1;
		}
		//result в int
		int result = 0;
		std::optional<int> charNumber = 0;

		while (i <= str.length() - 1)
		{
			charNumber = LetterToNumber(str[i]);
			if ((!charNumber) || (charNumber.value() > radix))
			{
				return std::nullopt;
			}
			if (result > ((INT32_MAX - charNumber.value()) / radix))
			{
				return std::nullopt;
			}
			
			result = result * radix + charNumber.value();
			i++;
		}
		if (isNegative)
		{
			result *= -1;
		}
		return result;
	}

	std::optional<char> NumberToChar(int remain)
	{
		const int DIF_BETW_NUMBER_OF_DIGIT_AND_LETTER = 7;
		const char CONST_FOR_CONVERT_CHAR_TO_DIGIT = '0';
		const char NEGATIVE_CHAR = '-';

		if ((remain >= 0) && (remain <= 9))
		{
			return remain + CONST_FOR_CONVERT_CHAR_TO_DIGIT;
		}
		if ((remain >= 10) && (remain <= MAX_RADIX))
		{
			return remain + CONST_FOR_CONVERT_CHAR_TO_DIGIT + DIF_BETW_NUMBER_OF_DIGIT_AND_LETTER;
		}
		//убрать лишние else
		return std::nullopt;
	}

	void Reverse(std::string& str)
	{
		for (int i = 0; i < str.length() / 2; ++i)
		{
			std::swap(str[i], str[str.length() - i - 1]);
		}
	}

	std::optional<std::string> IntToString(int number, int radix)
	{
		std::string str;
		//вынести проверку radix в отдельную функцию
		if (!isRadixInBounds(radix))
		{
			return std::nullopt;
		}

		bool isNegative = false;
		if (number < 0)
		{
			isNegative = true;
			number *= -1;
		}

		int remain = 0;
		while (number >= radix)
		{
			remain = number % radix;
			number -= remain;
			number /= radix;

			std::optional<char> digit = NumberToChar(remain);
			if (!digit)
			{
				return std::nullopt;
			}
			str.push_back(digit.value());
		}
		remain = number % radix;
		std::optional<char> digit = NumberToChar(remain);
		if (!digit)
		{
			return std::nullopt;
		}
		str.push_back(digit.value());

		if (isNegative)
		{
			str.push_back(NEGATIVE_CHAR);
		}
		Reverse(str);
		return str;
	}

	std::optional<IncomingValues> ConvertIncomingValues(Args& args)
	{
		IncomingValues intValues;
		std::optional<int> sourceNotationInt = StringToInt(args.sourceNotation, 10);
		if (!sourceNotationInt)
		{
			PrintError();
			return std::nullopt;
		}
		intValues.sourceNotation = sourceNotationInt.value();

		std::optional<int> destinationNotationInt = StringToInt(args.destinationNotation, 10);
		if (!destinationNotationInt)
		{
			PrintError();
			return std::nullopt;
		}
		intValues.destinationNotation = destinationNotationInt.value();

		std::optional<int> valueInt = StringToInt(args.value, sourceNotationInt.value());
		if (!valueInt)
		{
			PrintError();
			return std::nullopt;
		}
		intValues.value = valueInt.value();

		return intValues;
	}

	//разбить функцию на 2, где в одной будет перевод строки в 10-число
	bool ConvertValueInDestinationNotation(Args& args)
	{
		auto intValues = ConvertIncomingValues(args);
		if (!intValues)
		{
			return false;
		}

		std::optional<std::string> result = IntToString(intValues.value().value, intValues.value().destinationNotation);
		if (!result)
		{
			PrintError();
			return false;
		}

		std::cout << result.value() << std::endl;
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

	if (!ConvertValueInDestinationNotation(args.value()))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}