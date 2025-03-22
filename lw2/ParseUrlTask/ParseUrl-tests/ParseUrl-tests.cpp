#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ParseURL/ParseUrlModules.h"

TEST_CASE("Parse URL with port")
{
	URL urlParams;
	std::string url = "ftp://www.mysite.com:9801/docs/document1.html?page=30&lang=en#title";

	CHECK(ParseURL(url, urlParams));
	CHECK(urlParams.protocol == Protocol::FTP);
	CHECK(urlParams.port == 9801);
	CHECK(urlParams.host == "www.mysite.com");
	CHECK(urlParams.document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("Parse URL without port")
{
	URL urlParams;
	std::string url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";

	CHECK(ParseURL(url, urlParams));
	CHECK(urlParams.protocol == Protocol::HTTPS);
	CHECK(urlParams.port == 443);
	CHECK(urlParams.host == "www.mysite.com");
	CHECK(urlParams.document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("Parse URL without document")
{
	std::string url = "https://www.mysite.com";

	auto urlParams = ParseURL(url);

	CHECK();
	CHECK(urlParams.protocol == Protocol::HTTPS);
	CHECK(urlParams.port == 443);
	CHECK(urlParams.host == "www.mysite.com");
	CHECK(urlParams.document.empty());
}

TEST_CASE("Not correct URL")
{
	URL urlParams;
	std::string url = "htps:/";

	CHECK(!ParseURL(url, urlParams));
}

//протестировать все структуры URL отдельно в testCase