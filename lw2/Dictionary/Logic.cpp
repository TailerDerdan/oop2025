#include "Logic.h"
#include <algorithm>

// использовать optional
std::optional<std::vector<std::string>> GetTranslation(const std::string& word, Dictionary& dictionary)
{
	auto iter = dictionary.find(word);
	if (iter != dictionary.end())
	{
		return iter->second;
	}
	return std::nullopt;
}

void HandleSaving(Dictionary& dictionary, std::string term, std::istream& input, std::ostream& output, TypeOfUserMessage& typeMessage)
{
	std::string translation;
	std::getline(input, translation);
	if (translation == "")
	{
		typeMessage = TypeOfUserMessage::UssavedWord;
		PrintMessageForUser(output, typeMessage, term, translation);
		return;
	}
	std::vector<std::string> translations;
	translations.push_back(translation);
	dictionary.insert(std::make_pair(term, translations));
	typeMessage = TypeOfUserMessage::SavedWord;
	PrintMessageForUser(output, typeMessage, term, translation);
}

void PrintTranslations(std::vector<std::string>& translations, std::ostream& output)
{
	copy(translations.begin(), translations.end() - 1, std::ostream_iterator<std::string>(output, ", "));
	output << *(translations.end() - 1) << std::endl;
}

std::string StrToLower(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char ch) { return std::tolower(ch); });
	return result;
}

void PrintMessageForUser(std::ostream& output, const TypeOfUserMessage& typeOfMessage, const std::string& term, const std::string& translation)
{
	switch (typeOfMessage)
	{
		SavedWord:
			output << "Слово \"" << term << "\" сохранено в словаре как \"" << translation << "\"." << std::endl;
			break;
		UnsavedWord:
			output << "Слово \"" << term << "\" было проигнорировано" << std::endl;
			break;
		UnknowWord:
			output << "Неизвестное слово '" << term << "'. Введите перевод или пустую строку для отказа." << std::endl;
			break;
		default:
			break;
	}
}

void HandleWord(const std::string& word, Dictionary& dictionary, std::istream& input, std::ostream& output)
{
	std::string lowerWord = StrToLower(word);
	auto translations = GetTranslation(lowerWord, dictionary);
	TypeOfUserMessage typeMessage;
	if (!translations)
	{
		typeMessage = TypeOfUserMessage::UnknowWord;
		PrintMessageForUser(output, typeMessage, word, "");
		HandleSaving(dictionary, lowerWord, input, output, typeMessage);
	}
	else
	{
		PrintTranslations(translations.value(), output);
	}
}