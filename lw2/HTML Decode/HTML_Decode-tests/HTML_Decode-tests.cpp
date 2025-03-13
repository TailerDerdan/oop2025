#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ParseURL/HTMLDecode.h"

//разбить на section
//TEST_CASE("Verifying the identification of an html entity")
//{
//	std::map<std::string, std::string> specialStrs{ { "&quot;", "\"" }, { "&apos;", "'" },
//		{ "&gt;", ">" }, { "&lt;", "<" }, { "&amp;", "&" } };
//
//	std::string htmlEntity = "&quot;";
//	std::string neededChar = DecodeSpecialStr(htmlEntity);
//	CHECK(neededChar == specialStrs.at(htmlEntity));
//
//	htmlEntity = "&apos;";
//	neededChar = DecodeSpecialStr(htmlEntity);
//	CHECK(neededChar == specialStrs.at(htmlEntity));
//
//	htmlEntity = "&gt;";
//	neededChar = DecodeSpecialStr(htmlEntity);
//	CHECK(neededChar == specialStrs.at(htmlEntity));
//
//	htmlEntity = "&lt;";
//	neededChar = DecodeSpecialStr(htmlEntity);
//	CHECK(neededChar == specialStrs.at(htmlEntity));
//
//	htmlEntity = "&amp;";
//	neededChar = DecodeSpecialStr(htmlEntity);
//	CHECK(neededChar == specialStrs.at(htmlEntity));
//
//	htmlEntity = "&qwer;";
//	neededChar = DecodeSpecialStr(htmlEntity);
//	CHECK(neededChar == "&qwer;");
//}

TEST_CASE("Empty string give empty string")
{
	CHECK(DecodeHtml("").empty());
}

TEST_CASE("Test with all special characters")
{
	std::string result = DecodeHtml("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	CHECK(result == "Cat <says> \"Meow\". M&M\'s");
}

TEST_CASE("Test with multiline text")
{
	std::string result = DecodeHtml("The third most popular book of all time, &quot;Harry Potter&quot;, has sold over 400,000,000 copies &amp;\n\&apos;Titanic&apos; is a 1997 movie directed by James Cameron about the sinking of the ship &lt;Titanic&gt;.");
	CHECK(result == "The third most popular book of all time, \"Harry Potter\", has sold over 400,000,000 copies &\n'Titanic' is a 1997 movie directed by James Cameron about the sinking of the ship <Titanic>.");
}

TEST_CASE("Test without html entity")
{
	std::string result = DecodeHtml("A real hero human being");
	CHECK(result == "A real hero human being");
}

TEST_CASE("Test with incorrect html entity")
{
	std::string result = DecodeHtml("Cat &ltsays&gt; &quotMeow&quot;. M&amp;M&apos;s");
	CHECK(result == "Cat &ltsays&gt; &quotMeow&quot;. M&M\'s");
}

TEST_CASE("Test, when one entity start after previous")
{
	std::string result = DecodeHtml("&amp;lt;");
	CHECK(result == "&lt;");
}