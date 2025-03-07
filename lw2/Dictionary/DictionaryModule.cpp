#include "DictionaryModule.h"

const char OPENING_BRACKET = '[';
const char CLOSING_BRACKET = ']';
const std::string END = "...";
const std::string DELIMITER = ", ";

std::vector<std::string> ParseString(std::string& line)
{
	std::vector<std::string> result;
	std::string word;
	size_t posOfDelimetr = 0;

	while ((posOfDelimetr = line.find(DELIMITER)) != std::string::npos)
	{
		word = line.substr(0, posOfDelimetr);
		result.push_back(word);
		line.erase(0, posOfDelimetr + DELIMITER.length());
	}
	result.push_back(line);
	return result;
}

Dictionary ReadDictionaryFromFile(std::string dictionaryFilePath)
{
	Dictionary dictionary;
	std::ifstream dictionaryFile;

	dictionaryFile.open(dictionaryFilePath);
	if (!dictionaryFile.is_open())	
	{
		return dictionary;
	}

	std::string line;

	while (std::getline(dictionaryFile, line))
	{
		if (!line.empty())
		{
			size_t posOpeningBracket = line.find_first_of(OPENING_BRACKET);
			size_t posClosingBracket = line.find_first_of(CLOSING_BRACKET);
			std::string terms = line.substr(posOpeningBracket + 1, posClosingBracket - posOpeningBracket - 1);

			posClosingBracket = line.find_first_of(CLOSING_BRACKET);
			std::string translations = line.substr(posClosingBracket + 2);

			dictionary.insert(std::make_pair(ParseString(terms), ParseString(translations)));
		}
	}
}

void WorkWithDictionary(Dictionary& dictionary, std::istream& input)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (line == END)
		{
			break;
		}
		//HandleWord(line, dictionary);
	}
}

void HandleDictionary(std::istream& input, std::ostream& output, std::string dictionaryFilePath)
{
	Dictionary dictionary;
	try
	{
		dictionary = ReadDictionaryFromFile(dictionaryFilePath);
	}
	catch (const std::exception& exp)
	{
		output << exp.what() << std::endl;
	}

	WorkWithDictionary(dictionary, input);
	//PrintDicitionaryInFile(dictionary, dictionaryFilePath);
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