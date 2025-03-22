#pragma once

//��������� include
//������������� �����

#include <map>
#include <vector>
#include <string>
#include <optional>

// ������� �� ����� ������� ������� � ���������� �� �������

using Dictionary = std::map<std::string, std::vector<std::string>>;

//dictionary ���������� const &
std::optional<std::vector<std::string>> GetTranslations(const std::string& word, Dictionary& dictionary);
void AddNewTranslation(Dictionary& dictionary, const std::string& term, const std::string& translation);