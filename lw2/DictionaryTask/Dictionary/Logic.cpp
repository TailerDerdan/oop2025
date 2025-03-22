#include "Logic.h"
#include <algorithm>

std::string StrToLower(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

std::optional<std::vector<std::string>> GetTranslations(const std::string& word, Dictionary& dictionary)
{
	std::string lowerWord = StrToLower(word);
	auto iter = dictionary.find(lowerWord);
	if (iter != dictionary.end())
	{
		return iter->second;
	}
	return std::nullopt;
}

void AddNewTranslation(Dictionary& dictionary, const std::string& term, const std::string& translation)
{
	if (GetTranslations(term, dictionary))
	{
		return;
	}
	std::string lowerWord = StrToLower(term);
	std::vector<std::string> translations;
	translations.push_back(translation);
	dictionary.insert(std::make_pair(lowerWord, translations));
}