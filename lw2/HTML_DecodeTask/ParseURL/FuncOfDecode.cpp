#include "HTMLDecode.h"

//убрать ненужные include
#include <map>

std::string DecodeSpecialStr(const std::string& potentiolHtmlEntity)
{
	//использовать static
	static std::map<std::string, std::string> specialChar{ { "&quot;", "\"" }, { "&apos;", "'" },
		{ "&gt;", ">" }, { "&lt;", "<" }, { "&amp;", "&" } };

	//переписать обход цикла на [key, value]
	for (const auto& [htmlEntity, specialChar] : specialChar)
	{
		if (potentiolHtmlEntity == htmlEntity)
		{
			return specialChar;
		}
	}

	return potentiolHtmlEntity;
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

	//оптимизировать работу нахождение сущностей в строке
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
			std::string specialChar = DecodeSpecialStr(potentialHTMLEntity);
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