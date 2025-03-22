#include <iostream>
#include "ParseUrlModules.h"

void OutputInfoAboutUrl(URL& urlParams)
{
	std::cout << "HOST: " << urlParams.host << std::endl;
	std::cout << "PORT: " << urlParams.port << std::endl;
	std::cout << "DOC: " << urlParams.document << std::endl;
}

void ParsingUrl()
{
	std::string url;

	while (std::getline(std::cin, url))
	{
		auto urlParams = ParseURL(url);
		if (!urlParams)
		{
			std::cout << "Invalid URL" << std::endl;
			continue;
		}
		OutputInfoAboutUrl(urlParams.value());
	}
}

int main()
{
	ParsingUrl();
}