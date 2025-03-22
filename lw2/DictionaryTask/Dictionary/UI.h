#pragma once

#include "Logic.h"

struct Args
{
	std::string dictionaryFilePath;
};

Dictionary ReadDictionaryFromFile(std::fstream& dictionaryFile);
void WorkWithDictionary(Dictionary& dictionary, std::istream& input, std::ostream& output, bool& isDictionaryChanged);
void PrintDictionaryInFile(Dictionary& dictionary, std::fstream& dictionaryFile);