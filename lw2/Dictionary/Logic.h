#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <optional>

using Dictionary = std::map<std::string, std::vector<std::string>>;

enum class TypeOfUserMessage
{
	UnknowWord,
	UssavedWord,
	SavedWord,
};

std::optional<std::vector<std::string>> GetTranslation(const std::string& word, Dictionary& dictionary);
void HandleSaving(Dictionary& dictionary, std::string term, std::istream& input, std::ostream& output, TypeOfUserMessage& typeMessage);
std::string StrToLower(const std::string& str);
void HandleWord(const std::string& word, Dictionary& dictionary, std::istream& input, std::ostream& output);