#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

std::string DecodeSpecialChar(std::string& temp);
std::string DecodeHtml(const std::string& html);
void ReadText(std::string& text, std::istream& input);