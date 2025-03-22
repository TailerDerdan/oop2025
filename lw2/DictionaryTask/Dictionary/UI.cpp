#include "UI.h"
#include <iostream>
#include <fstream>
#include <algorithm>

const char OPENING_BRACKET = '[';
const char CLOSING_BRACKET = ']';
const std::string END = "...";
const std::string DELIMITER = ", ";

enum class TypeOfUserMessage
{
	SavedWord,
	UssavedWord,
	UnknowWord
};

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

//исправить слово
void PrintDictionaryInFile(Dictionary& dictionary, std::fstream& dictionaryFile)
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

void PrintMessageForUser(std::ostream& output, const TypeOfUserMessage& typeOfMessage, const std::string& term, const std::string& translation)
{
	switch (typeOfMessage)
	{
	case TypeOfUserMessage::SavedWord:
		output << "Слово \"" << term << "\" сохранено в словаре как \"" << translation << "\"." << std::endl;
		break;
	case TypeOfUserMessage::UssavedWord:
		output << "Слово \"" << term << "\" было проигнорировано" << std::endl;
		break;
	case TypeOfUserMessage::UnknowWord:
		output << "Неизвестное слово '" << term << "'. Введите перевод или пустую строку для отказа." << std::endl;
		break;
	default:
		break;
	}
}

std::optional<std::string> GetTranslation(std::istream& input, std::ostream& output, const std::string& lowerWord)
{
	std::string translation;
	std::getline(input, translation);

	if (translation == "")
	{
		PrintMessageForUser(output, TypeOfUserMessage::UssavedWord, lowerWord, translation);
		return std::nullopt;
	}
	return translation;
}

void PrintTranslations(const std::vector<std::string>& translations, std::ostream& output)
{
	copy(translations.begin(), translations.end() - 1, std::ostream_iterator<std::string>(output, ", "));
	output << *(translations.end() - 1) << std::endl;
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
		isDictionaryChanged = true;

		auto translations = GetTranslations(word, dictionary);
		if (!translations)
		{
			PrintMessageForUser(output, TypeOfUserMessage::UnknowWord, word, "");
			auto translation = GetTranslation(input, output, word);
			if (translation)
			{
				AddNewTranslation(dictionary, word, translation.value());
			}
			continue;
		}
		PrintTranslations(translations.value(), output);
	}
}