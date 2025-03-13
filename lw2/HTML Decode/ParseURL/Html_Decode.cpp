#include "HTMLDecode.h"
#include <iostream>

void ReadText(std::string& text, std::istream& input)
{
	std::string line;
	while (!std::cin.eof())
	{
		std::getline(input, line);
		text.append(line);
	}
}

int main()
{
	std::string text;
	ReadText(text, std::cin);

	text = DecodeHtml(text);

	copy(text.begin(), text.end(), std::ostream_iterator<char>(std::cout));

	return EXIT_SUCCESS;
}