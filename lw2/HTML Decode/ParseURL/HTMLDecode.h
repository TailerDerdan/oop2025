#pragma once

#include <fstream>
#include <iostream>
#include <string>

std::string DecodeSpecialStr(std::string& htmlEntity);
std::string DecodeHtml(const std::string& html);