#include <catch2/catch_test_macros.hpp>

#include "CString.h"

//добавить тесты на clear

TEST_CASE("constructors")
{
	SECTION("base constructor")
	{
		CString cstr;
		CHECK(cstr.GetLength() == 0);
		CHECK(cstr.GetCapacity() == 1);
		CHECK((strcmp(cstr.GetStringData(), "")) == 0);
	}

	SECTION("constructor char*")
	{
		CString cstr("string");
		CHECK(cstr.GetLength() == 6);
		CHECK(cstr.GetCapacity() == 7);
		CHECK((strcmp(cstr.GetStringData(), "string")) == 0);
	}

	SECTION("constructor char* with length")
	{
		CString cstr("string", 3);
		CHECK(cstr.GetLength() == 3);
		CHECK(cstr.GetCapacity() == 4);
		CHECK((strcmp(cstr.GetStringData(), "str")) == 0);

		CString cstr2("string", 50);
		CHECK(cstr2.GetLength() == 50);
		CHECK(cstr2.GetCapacity() == 51);
		CHECK((strcmp(cstr2.GetStringData(), "string")) == 0);
	}

	SECTION("constructor CString")
	{
		CString cstr("string");
		CString cstr2(cstr);
		CHECK(cstr.GetLength() == cstr2.GetLength());
		CHECK(cstr.GetCapacity() == cstr2.GetCapacity());
		CHECK((strcmp(cstr.GetStringData(), cstr2.GetStringData())) == 0);
	}

	SECTION("copy constructor")
	{
		CString cstr = "string";
		CString cstr2(cstr);
		CHECK(cstr.GetLength() == cstr.GetLength());
		CHECK(cstr.GetCapacity() == cstr.GetCapacity());
		CHECK((strcmp(cstr.GetStringData(), cstr.GetStringData())) == 0);
	}

	SECTION("move constructor")
	{
		CString cstr("string");
		CString cstr2(std::move(cstr));
		CHECK(cstr2.GetLength() == 6);
		CHECK(cstr2.GetCapacity() == 7);
		CHECK((strcmp(cstr2.GetStringData(), "string")) == 0);

		CHECK(cstr.GetLength() == 0);
		CHECK(cstr.GetCapacity() == 0);
		CHECK(cstr.GetStringData() == nullptr);
	}

	SECTION("constructor std::string")
	{
		std::string str = "string";
		CString cstr(str);
		CHECK(cstr.GetLength() == str.size());
		CHECK(cstr.GetCapacity() == 7);
		CHECK((strcmp(cstr.GetStringData(), str.c_str())) == 0);
	}
}

TEST_CASE("susbtr")
{
	CString cstr("string");
	CString cstr2 = cstr.SubString(3, 2);
	CHECK(cstr2.GetLength() == 2);
	CHECK(cstr2.GetCapacity() == 3);
	CHECK((strcmp(cstr2.GetStringData(), "in")) == 0);
	CHECK_THROWS_AS(cstr.SubString(10, 12), std::out_of_range);
	CHECK_THROWS_AS(cstr.SubString(10, 4), std::out_of_range);
}
//добавить тестов для clear
TEST_CASE("clear")
{
	CString cstr("string");
	cstr.Clear();
	CHECK(cstr.GetLength() == 0);
	CHECK(cstr.GetCapacity() == 1);
	CHECK((strcmp(cstr.GetStringData(), "")) == 0);
}

TEST_CASE("operations")
{
	SECTION("operation []")
	{
		CString cstr("string");
		CHECK(cstr[3] == 'i');
		CHECK_THROWS_AS(cstr[10], std::out_of_range);

		cstr[0] = 'o';
		CHECK(cstr[0] == 'o');
	}

	SECTION("const operation []")
	{
		const CString cstr("string");
		CHECK(cstr[3] == 'i');
		CHECK_THROWS_AS(cstr[10], std::out_of_range);
	}

	SECTION("operation =")
	{
		CString cstr("string");
		auto cstr2 = cstr;
		CHECK(cstr2.GetLength() == cstr.GetLength());
		CHECK(cstr2.GetCapacity() == cstr.GetCapacity());
		CHECK((strcmp(cstr.GetStringData(), cstr2.GetStringData())) == 0);

		CHECK(cstr2.GetLength() == 6);
		CHECK(cstr2.GetCapacity() == 7);
		CHECK((strcmp(cstr2.GetStringData(), "string")) == 0);

		CHECK(cstr.GetLength() == 6);
		CHECK(cstr.GetCapacity() == 7);
		CHECK((strcmp(cstr.GetStringData(), "string")) == 0);

		cstr = cstr;
		CHECK(cstr.GetLength() == 6);
		CHECK(cstr.GetCapacity() == 7);
		CHECK((strcmp(cstr.GetStringData(), "string")) == 0);
	}

	SECTION("operation + CString")
	{
		CString cstr("string");
		CString cstr2(" 12");
		auto cstr3 = cstr + cstr2;
		CHECK(cstr3.GetLength() == 9);
		CHECK(cstr3.GetCapacity() == 14);
		CHECK((strcmp(cstr3.GetStringData(), "string 12")) == 0);

		cstr = cstr + cstr2;
		CHECK(cstr.GetLength() == 9);
		CHECK(cstr.GetCapacity() == 14);
		CHECK((strcmp(cstr.GetStringData(), "string 12")) == 0);
	}

	SECTION("operation + std::string")
	{
		CString cstr("string");
		std::string cstr2(" 12");
		auto cstr3 = cstr + cstr2;
		CHECK(cstr3.GetLength() == 9);
		CHECK(cstr3.GetCapacity() == 14);
		CHECK((strcmp(cstr3.GetStringData(), "string 12")) == 0);
	}

	SECTION("operation + char*")
	{
		CString cstr("string");
		char* cstr2 = " 12";
		auto cstr3 = cstr + cstr2;
		CHECK(cstr3.GetLength() == 9);
		CHECK(cstr3.GetCapacity() == 14);
		CHECK((strcmp(cstr3.GetStringData(), "string 12")) == 0);
	}

	SECTION("operation +=")
	{
		CString cstr("string");
		CString cstr2(" 12");
		cstr += cstr2;
		CHECK(cstr.GetLength() == 9);
		CHECK(cstr.GetCapacity() == 14);
		CHECK((strcmp(cstr.GetStringData(), "string 12")) == 0);
	}

	SECTION("bool operation")
	{
		CString cstr("aa");
		CString cstr2("b");
		CString cstr3("aa");

		CHECK_FALSE(cstr == cstr2);
		CHECK(cstr == cstr3);
		CHECK_FALSE(cstr2 == cstr3);
		CHECK(cstr == cstr);
		CHECK(cstr2 == cstr2);
		CHECK(cstr3 == cstr3);

		CHECK(cstr != cstr2);
		CHECK_FALSE(cstr != cstr3);
		CHECK(cstr2 != cstr3);
		CHECK_FALSE(cstr != cstr);
		CHECK_FALSE(cstr2 != cstr2);
		CHECK_FALSE(cstr3 != cstr3);

		CHECK_FALSE(cstr > cstr2);
		CHECK_FALSE(cstr > cstr3);
		CHECK(cstr2 > cstr3);
		CHECK_FALSE(cstr > cstr);
		CHECK_FALSE(cstr2 > cstr2);
		CHECK_FALSE(cstr3 > cstr3);

		CHECK_FALSE(cstr >= cstr2);
		CHECK(cstr >= cstr3);
		CHECK(cstr2 >= cstr3);
		CHECK(cstr >= cstr);
		CHECK(cstr2 >= cstr2);
		CHECK(cstr3 >= cstr3);

		CHECK(cstr < cstr2);
		CHECK_FALSE(cstr < cstr3);
		CHECK_FALSE(cstr2 < cstr3);
		CHECK_FALSE(cstr < cstr);
		CHECK_FALSE(cstr2 < cstr2);
		CHECK_FALSE(cstr3 < cstr3);

		CHECK(cstr <= cstr2);
		CHECK(cstr <= cstr3);
		CHECK_FALSE(cstr2 <= cstr3);
		CHECK(cstr <= cstr);
		CHECK(cstr2 <= cstr2);
		CHECK(cstr3 <= cstr3);
	}

	SECTION("operation >> and <<")
	{
		CString cstr("string");

		std::ostringstream os;
		os << cstr;
		CHECK(os.str() == "string");

		std::istringstream is("string2");
		CString cstr2;
		is >> cstr2;
		CHECK(std::strcmp(cstr2.GetStringData(), "string2") == 0);
	}
}

//добавить тест на разыменование end и begin и выход за границы
//добавить тест на проверку границ
TEST_CASE("iterators")
{
	SECTION("base")
	{
		CString cstr("string");
		std::string str;
		for (auto ch : cstr)
		{
			str += ch;
		}
		CHECK(str == "string");
	}

	SECTION("*begin and *end")
	{
		CString cstr("string");
		auto it = cstr.begin();
		auto it2 = cstr.end();
		it = it - 1;
		it2 = it2 + 1;
		CHECK(std::strcmp(it, "") == 0);
		CHECK(std::strcmp(it2, "") == 0);
		CHECK_FALSE(it == it2);
	}

	SECTION("const base")
	{
		CString cstr("string");
		auto it = cstr.сbegin();
		CHECK(*it == 's');
	}

	SECTION("const reverse")
	{
		CString cstr("string");
		const auto it = cstr.rbegin();
		const auto it2 = cstr.crbegin();
		CHECK(*it == 'g');
		CHECK(*it2 == 'g');
	}

	SECTION("plus and minus")
	{
		CString cstr("string");
		CHECK((cstr.end() - cstr.begin()) == 6);
		CHECK(std::strcmp(cstr.begin(), "string") == 0);
	}

	SECTION("-- and ++")
	{
		CString cstr("string");
		auto it = cstr.begin();

		it++;
		CHECK(std::strcmp(it, "tring") == 0);

		it--;
		CHECK(std::strcmp(it, "string") == 0);

		CHECK(*it == 's');
		it++;
		CHECK(*it == 't');
	}

	SECTION("reverse")
	{
		CString cstr("string");
		std::string str;
		for (auto it = cstr.rbegin(); it != cstr.rend(); ++it)
		{
			str += *it;
		}
		CHECK(str == "gnirts");
	}
}