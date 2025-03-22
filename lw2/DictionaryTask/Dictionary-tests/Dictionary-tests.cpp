#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Dictionary/Logic.h"
#include <sstream>
#include <windows.h>

//написать тесты для дополнительных функций

TEST_CASE("Get translations")
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string ball = "ball";
	std::vector<std::string> translationsBall = { "мяч", "бал", "шар" };
	Dictionary dictionary = { { ball, translationsBall } };
	
	//добавить тест на вектор
	SECTION("good test")
	{
		CHECK(GetTranslations(ball, dictionary).value()[0] == "мяч");
	}

	SECTION("word with mixed case")
	{
		CHECK(GetTranslations("bALL", dictionary).value()[0] == "мяч");
	}
	
	SECTION("non-existent word in dictionary")
	{
		CHECK(!GetTranslations("fish", dictionary));
	}
}

TEST_CASE("Handle saving")
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string ball = "ball";
	std::string translationBall = "мяч";
	Dictionary dictionary = {};

	//переделать через section
	AddNewTranslation(dictionary, ball, translationBall);
	CHECK(dictionary[ball][0] == translationBall);
	AddNewTranslation(dictionary, ball, translationBall);
	CHECK(dictionary.size() == 1);
}