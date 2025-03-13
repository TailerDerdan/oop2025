#include "UI.h"
#include <algorithm>

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

Dictionary ReadDictionaryFromFile(std::fstream& dictionaryFile)
{
	Dictionary dictionary;
	std::string line;

	while (std::getline(dictionaryFile, line))
	{
		if (!line.empty())
		{
			size_t posOpeningBracket = line.find_first_of(OPENING_BRACKET);
			size_t posClosingBracket = line.find_first_of(CLOSING_BRACKET);
			std::string term = line.substr(posOpeningBracket + 1, posClosingBracket - posOpeningBracket - 1);

			posClosingBracket = line.find_first_of(CLOSING_BRACKET);
			std::string translations = line.substr(posClosingBracket + 2);

			dictionary.insert(std::make_pair(term, ParseString(translations)));
		}
	}
	return dictionary;
}

void PrintDicitionaryInFile(Dictionary& dictionary, std::fstream& dictionaryFile)
{
	for (auto iter : dictionary)
	{
		dictionaryFile << OPENING_BRACKET;
		dictionaryFile << iter.first;
		dictionaryFile << CLOSING_BRACKET << " ";
		copy(iter.second.begin(), iter.second.end() - 1, std::ostream_iterator<std::string>(dictionaryFile, ", "));
		dictionaryFile << iter.second.at(iter.second.size() - 1);
		dictionaryFile << std::endl;
	}
}

void WorkWithDictionary(Dictionary& dictionary, std::istream& input, std::ostream& output, bool& isDictionaryChanged)
{
	std::string word;
	while (std::getline(input, word))
	{
		if (word == END)
		{
			break;
		}
		HandleWord(word, dictionary, input, output);
		isDictionaryChanged = true;
	}
}