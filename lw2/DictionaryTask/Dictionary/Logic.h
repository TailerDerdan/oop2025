#pragma once

//почистить include
//переименовать файлы

#include <map>
#include <vector>
#include <string>
#include <optional>

// разбить на более простые функции и избавиться от потоков

using Dictionary = std::map<std::string, std::vector<std::string>>;

//dictionary передавать const &
std::optional<std::vector<std::string>> GetTranslations(const std::string& word, Dictionary& dictionary);
void AddNewTranslation(Dictionary& dictionary, const std::string& term, const std::string& translation);