#include <catch2/catch_test_macros.hpp>
#include "StringList.h"

namespace
{
	const std::string FIRST = "first";
	const std::string SECOND = "second";
	const std::string THIRD = "third";
}

TEST_CASE("check constructors")
{
	SECTION("default")
	{
		StringList stringList;
		CHECK(stringList.size() == 0);
		CHECK(stringList.empty());
		CHECK(stringList.begin() == stringList.end());
		CHECK_THROWS_AS(*stringList.begin(), std::out_of_range);
	}

	SECTION("constructors with {...}")
	{
		StringList stringList = {FIRST, SECOND, THIRD};
		CHECK(stringList.size() == 3);
		CHECK_FALSE(stringList.empty());
	}

	SECTION("copy constructors")
	{
		StringList stringList = {FIRST, SECOND, THIRD};
		auto s2(stringList);
		CHECK(s2.size() == 3);
		CHECK_FALSE(s2.empty());
		CHECK(s2.size() == stringList.size());
	}

	SECTION("move constructors")
	{
		StringList stringList = {FIRST, SECOND, THIRD};
		auto s2(std::move(stringList));
		CHECK(s2.size() == 3);
		CHECK_FALSE(s2.empty());
		CHECK(stringList.size() == 0);
		CHECK(stringList.empty());
		CHECK_FALSE(s2.size() == stringList.size());

		StringList sl = {FIRST, SECOND, THIRD};
		sl = std::move(sl);
		CHECK(sl.size() == 3);
	}
}

TEST_CASE("operators =")
{
	SECTION("copy =")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto sl2 = sl;
		CHECK(sl2.size() == sl.size());

		CHECK(sl2.size() == 3);
		CHECK_FALSE(sl2.empty());

		CHECK(sl.size() == 3);
		CHECK_FALSE(sl.empty());
	}

	SECTION("move =")
	{
		StringList sl = StringList({FIRST, SECOND, THIRD});
		CHECK(sl.size() == 3);
		CHECK_FALSE(sl.empty());
	}

	SECTION("var1 = var1")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		sl = sl;
		CHECK(sl.size() == 3);
		CHECK_FALSE(sl.empty());
	}
}

TEST_CASE("general operators")
{
	SECTION("push_back")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		sl.push_back("new");
		CHECK(sl.size() == 4);
		CHECK(*(sl.begin()) == FIRST);
		CHECK(*(--sl.end()) == "new");
	}

	SECTION("push_front")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		sl.push_front("new");
		CHECK(sl.size() == 4);
		CHECK(*(sl.begin()) == "new");
		CHECK(*(--sl.end()) == THIRD);
	}

	SECTION("pop_back")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto str = sl.pop_back();
		CHECK(sl.size() == 2);
		CHECK(str == THIRD);
		CHECK(*(sl.begin()) == FIRST);
		CHECK(*(--sl.end()) == SECOND);

		StringList sl2;
		CHECK_THROWS_AS(sl2.pop_back(), std::out_of_range);
	}

	SECTION("pop_front")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto str = sl.pop_front();
		CHECK(sl.size() == 2);
		CHECK(str == FIRST);
		CHECK(*(sl.begin()) == SECOND);
		CHECK(*(--sl.end()) == THIRD);

		StringList sl2;
		CHECK_THROWS_AS(sl2.pop_front(), std::out_of_range);
	}

	SECTION("clear")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		CHECK(sl.size() == 3);
		CHECK_FALSE(sl.empty());

		sl.clear();
		CHECK(sl.size() == 0);
		CHECK(sl.empty());

		sl.clear();
		CHECK(sl.size() == 0);
		CHECK(sl.empty());

		StringList sl2;
		for (int i = 0; i < 100000; ++i)
			sl.push_back(std::to_string(i));
		CHECK_NOTHROW(sl.clear());
		CHECK(sl.empty());
	}
}

TEST_CASE("iterators")
{
	SECTION("base")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto bg = sl.begin();
		auto end = sl.end();
		CHECK(*bg == FIRST);
		CHECK_THROWS_AS(*end, std::out_of_range);
		CHECK(bg != end);
	}

	SECTION("const base")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto bg = sl.cbegin();
		auto end = sl.cend();
		CHECK(*bg == FIRST);
		CHECK_THROWS_AS(*end, std::out_of_range);
		CHECK(bg != end);
	}

	SECTION("-- and ++")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto bg = sl.begin();
		auto end = sl.end();
		CHECK(*bg == FIRST);

		bg++;
		end--;
		CHECK(*bg == SECOND);
		CHECK(*end == THIRD);

		--bg;
		--end;
		CHECK(*bg == FIRST);
		CHECK(*end == SECOND);

		++bg;
		end++;
		CHECK(*bg == SECOND);
		CHECK(*end == THIRD);

		bg--;
		--end;
		CHECK(*bg == FIRST);
		CHECK(*end == SECOND);
	}

	SECTION("check borders ++end and --begin")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto bg = sl.begin();
		auto end = sl.end();
		CHECK_THROWS_AS(--bg, std::out_of_range);
		CHECK_THROWS_AS(end++, std::out_of_range);
		CHECK_THROWS_AS(*end, std::out_of_range);
	}

	SECTION("range based for")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		std::vector<std::string> result;
		for (auto str : sl)
		{
			result.push_back(str);
		}
		CHECK(result[0] == FIRST);
		CHECK(result[1] == SECOND);
		CHECK(result[2] == THIRD);

		result.clear();
	}

	SECTION("reverse range based for")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		std::vector<std::string> result;
		for (auto iter = sl.rbegin(); iter != sl.rend(); ++iter)
		{
			result.push_back(*iter);
		}
		CHECK(result[0] == THIRD);
		CHECK(result[1] == SECOND);
		CHECK(result[2] == FIRST);

		result.clear();

		for (auto iter = sl.crbegin(); iter != sl.crend(); ++iter)
		{
			result.push_back(*iter);
		}
		CHECK(result[0] == THIRD);
		CHECK(result[1] == SECOND);
		CHECK(result[2] == FIRST);
	}

	SECTION("insert")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto it = sl.begin();
		sl.Insert("new", it);
		CHECK(*(sl.begin()) == "new");
	}

	SECTION("delete")
	{
		StringList sl = {FIRST, SECOND, THIRD};
		auto it = sl.begin();
		it++;
		it = sl.Delete(it);
		CHECK(*(it) == THIRD);

		StringList sl2 = {FIRST, SECOND, THIRD};
		CHECK_THROWS_AS(sl2.Delete(sl2.end()), std::out_of_range);
	}
}