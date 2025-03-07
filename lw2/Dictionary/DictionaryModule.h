#pragma once

#include <fstream>
#include <map>
#include <optional>
#include <string>
#include <vector>
#include <windows.h>
#include <stdexcept>

struct Args
{
	std::string dictionaryFilePath;
};

using Dictionary = std::map<std::vector<std::string>, std::vector<std::string>>;



std::vector<std::string> ParseString(std::string& line);
Dictionary ReadDictionaryFromFile(std::string dictionaryFilePath);
void WorkWithDictionary(Dictionary& dictionary, std::istream& input);
void HandleDictionary(std::istream& input, std::ostream& output, std::string dictionaryFilePath);

Args ParseArgs(int argc, char* argv[]);