#include "modules.h"

std::string DecodeSpecialChar(std::string& temp)
{
	std::map<std::string, std::string> specialChar{ { "&quot;", "\"" }, { "&apos;", "'" },
		{ "&gt;", ">" }, { "&lt;", "<" }, { "&amp;", "&" } };

	for (auto iter : specialChar)
	{
		if (temp == iter.first)
		{
			return iter.second;
		}
	}

	return temp;
}

std::string DecodeHtml(const std::string& html)
{
	if (html.empty())
	{
		return html;
	}

	std::string result;

	size_t previousStartPos = 0;
	size_t startPosSpecialChar = 0;
	size_t endPosSpecialChar = 0;

	while (startPosSpecialChar <= html.length() && endPosSpecialChar <= html.length())
	{
		previousStartPos = startPosSpecialChar;
		startPosSpecialChar = html.find('&', startPosSpecialChar);
		endPosSpecialChar = html.find(';', startPosSpecialChar);

		std::string potentialHTMLEntity;
		if (startPosSpecialChar <= html.length())
		{
			potentialHTMLEntity.append(html, startPosSpecialChar, endPosSpecialChar - startPosSpecialChar + 1);
		}

		if (!potentialHTMLEntity.empty())
		{
			std::string specialChar = DecodeSpecialChar(potentialHTMLEntity);
			result.append(html, previousStartPos, startPosSpecialChar - previousStartPos).append(specialChar);
			startPosSpecialChar += potentialHTMLEntity.size();
		}
		if (potentialHTMLEntity.empty())
		{
			result.append(html, previousStartPos, html.size() - previousStartPos);
		}
	}
	return result;
}

void ReadText(std::string& text, std::istream& input)
{
	std::string line;
	while (!std::cin.eof())
	{
		std::getline(input, line);
		text.append(line);
	}
}