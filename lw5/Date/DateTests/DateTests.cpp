#include <catch2/catch_test_macros.hpp>
#include "../CDate/CDate.h"
#include "catch2/generators/catch_generators.hpp"

TEST_CASE("negative timestamp")
{
	CDate date1(-1000);
	REQUIRE(date1.GetMonth() == Month::JANUARY);
	REQUIRE(date1.GetDay() == 1);
	REQUIRE(date1.GetWeekDay() == WeekDay::THURSDAY);
	REQUIRE(date1.GetYear() == 1970);
}

TEST_CASE("positive timestamp")
{
	CDate date1(0);
	REQUIRE(date1.GetMonth() == Month::JANUARY);
	REQUIRE(date1.GetDay() == 1);
	REQUIRE(date1.GetWeekDay() == WeekDay::THURSDAY);
	REQUIRE(date1.GetYear() == 1970);

	CDate date2(86400);
	REQUIRE(date2.GetMonth() == Month::JANUARY);
	REQUIRE(date2.GetDay() == 2);
	REQUIRE(date2.GetWeekDay() == WeekDay::FRIDAY);
	REQUIRE(date2.GetYear() == 1970);
}

TEST_CASE("negative dd.mm.yy")
{
	CDate date1(-30, Month::JANUARY, 1999);
	REQUIRE(date1.GetMonth() == Month::JANUARY);
	REQUIRE(date1.GetDay() == 1);
	REQUIRE(date1.GetWeekDay() == WeekDay::THURSDAY);
	REQUIRE(date1.GetYear() == 1970);

	CDate date2(30, Month::JANUARY, -1999);
	REQUIRE(date2.GetMonth() == Month::JANUARY);
	REQUIRE(date2.GetDay() == 1);
	REQUIRE(date2.GetWeekDay() == WeekDay::THURSDAY);
	REQUIRE(date2.GetYear() == 1970);

	CDate date3(30, Month::JANUARY, 1600);
	REQUIRE(date3.GetMonth() == Month::JANUARY);
	REQUIRE(date3.GetDay() == 1);
	REQUIRE(date3.GetWeekDay() == WeekDay::THURSDAY);
	REQUIRE(date3.GetYear() == 1970);

	CDate date4(30, Month::JANUARY, 10000);
	REQUIRE(date4.GetMonth() == Month::JANUARY);
	REQUIRE(date4.GetDay() == 1);
	REQUIRE(date4.GetWeekDay() == WeekDay::THURSDAY);
	REQUIRE(date4.GetYear() == 1970);
}

TEST_CASE("positive dd.mm.yy")
{
	CDate date1(12, Month::AUGUST, 2026);
	REQUIRE(date1.GetMonth() == Month::AUGUST);
	REQUIRE(date1.GetDay() == 12);
	REQUIRE(date1.GetWeekDay() == WeekDay::WEDNESDAY);
	REQUIRE(date1.GetYear() == 2026);

	CDate date2(31, Month::DECEMBER, 9999);
	REQUIRE(date2.GetMonth() == Month::DECEMBER);
	REQUIRE(date2.GetDay() == 31);
	REQUIRE(date2.GetWeekDay() == WeekDay::FRIDAY);
	REQUIRE(date2.GetYear() == 9999);
}

TEST_CASE("increment")
{
	CDate date1(27, Month::FEBRUARY, 2000);
	date1++;
	REQUIRE(date1.GetDay() == 28);
	++date1;
	REQUIRE(date1.GetDay() == 29);
	date1++;
	REQUIRE(date1.GetDay() == 1);
	REQUIRE(date1.GetMonth() == Month::MARCH);

	CDate date2(31, Month::DECEMBER, 2000);
	date2++;
	REQUIRE(date2.GetDay() == 1);
	REQUIRE(date2.GetMonth() == Month::JANUARY);
	REQUIRE(date2.GetYear() == 2001);
}

TEST_CASE("decrement")
{
	CDate date1(1, Month::FEBRUARY, 2000);
	date1--;
	REQUIRE(date1.GetMonth() == Month::JANUARY);
	REQUIRE(date1.GetDay() == 31);

	--date1;
	REQUIRE(date1.GetMonth() == Month::JANUARY);
	REQUIRE(date1.GetDay() == 30);

	CDate date2(1, Month::JANUARY, 2000);
	--date2;
	REQUIRE(date2.GetMonth() == Month::DECEMBER);
	REQUIRE(date2.GetDay() == 31);
	REQUIRE(date2.GetYear() == 1999);

	date2--;
	REQUIRE(date2.GetMonth() == Month::DECEMBER);
	REQUIRE(date2.GetDay() == 30);
}

TEST_CASE("plus")
{
	CDate date1(1, Month::FEBRUARY, 2000);
	date1 = date1 + 10;
	REQUIRE(date1.GetMonth() == Month::FEBRUARY);
	REQUIRE(date1.GetDay() == 11);

	date1 = date1 + 31;
	REQUIRE(date1.GetMonth() == Month::MARCH);
	REQUIRE(date1.GetDay() == 13);

	date1 = date1 + (-31);
	REQUIRE(date1.GetMonth() == Month::FEBRUARY);
	REQUIRE(date1.GetDay() == 11);

	date1 = date1 + 366;
	REQUIRE(date1.GetMonth() == Month::FEBRUARY);
	REQUIRE(date1.GetDay() == 11);
	REQUIRE(date1.GetYear() == 2001);

	CDate date2(31, Month::DECEMBER, 9999);
	date2 = date2 + 1;
	REQUIRE(date2.GetDay() == 1);
	REQUIRE(date2.GetYear() == 1970);
	REQUIRE(date2.GetMonth() == Month::JANUARY);

	CDate date3(31, Month::JANUARY, 1970);
	date3 = date3 + (-60);
	REQUIRE(date3.GetDay() == 1);
	REQUIRE(date3.GetYear() == 1970);
	REQUIRE(date3.GetMonth() == Month::JANUARY);

	CDate date4(31, Month::JANUARY, 1970);
	CDate date5;
	date5 = 1 + date4;
	REQUIRE(date5.GetDay() == 1);
	REQUIRE(date5.GetYear() == 1970);
	REQUIRE(date5.GetMonth() == Month::FEBRUARY);

	date5 = (-60) +  date4;
	REQUIRE(date5.GetDay() == 1);
	REQUIRE(date5.GetYear() == 1970);
	REQUIRE(date5.GetMonth() == Month::JANUARY);
}

TEST_CASE("plus and equel")
{
	CDate date1(1, Month::FEBRUARY, 2000);
	date1 += 10;
	REQUIRE(date1.GetMonth() == Month::FEBRUARY);
	REQUIRE(date1.GetDay() == 11);

	date1 += 31;
	REQUIRE(date1.GetMonth() == Month::MARCH);
	REQUIRE(date1.GetDay() == 13);

	date1 += (-31);
	REQUIRE(date1.GetMonth() == Month::FEBRUARY);
	REQUIRE(date1.GetDay() == 11);

	date1 += 366;
	REQUIRE(date1.GetMonth() == Month::FEBRUARY);
	REQUIRE(date1.GetDay() == 11);
	REQUIRE(date1.GetYear() == 2001);

	CDate date2(31, Month::DECEMBER, 9999);
	date2 += 1;
	REQUIRE(date2.GetDay() == 1);
	REQUIRE(date2.GetYear() == 1970);
	REQUIRE(date2.GetMonth() == Month::JANUARY);

	CDate date3(31, Month::JANUARY, 1970);
	date3 += (-60);
	REQUIRE(date3.GetDay() == 1);
	REQUIRE(date3.GetYear() == 1970);
	REQUIRE(date3.GetMonth() == Month::JANUARY);
}

TEST_CASE("minus")
{
	CDate date1(1, Month::MARCH, 2000);
	date1 = date1 - 10;
	REQUIRE(date1.GetMonth() == Month::FEBRUARY);
	REQUIRE(date1.GetDay() == 20);

	date1 = date1 - (-10);
	REQUIRE(date1.GetMonth() == Month::MARCH);
	REQUIRE(date1.GetDay() == 1);

	date1 = date1 - 366;
	REQUIRE(date1.GetMonth() == Month::MARCH);
	REQUIRE(date1.GetDay() == 1);
	REQUIRE(date1.GetYear() == 1999);

	CDate date2(31, Month::DECEMBER, 9999);
	date2 = date2 - (-1);
	REQUIRE(date2.GetDay() == 1);
	REQUIRE(date2.GetYear() == 1970);
	REQUIRE(date2.GetMonth() == Month::JANUARY);

	CDate date3(31, Month::JANUARY, 1970);
	date3 = date3 - 60;
	REQUIRE(date3.GetDay() == 1);
	REQUIRE(date3.GetYear() == 1970);
	REQUIRE(date3.GetMonth() == Month::JANUARY);

	CDate date4(25, Month::MARCH, 2026);
	CDate date5(25, Month::FEBRUARY, 2026);
	auto days = date4 - date5;
	REQUIRE(days == 28);
	days = date4 - date5;
	REQUIRE(days == 28);
}

TEST_CASE("minus and equel")
{
	CDate date1(1, Month::MARCH, 2000);
	date1 -= 10;
	REQUIRE(date1.GetMonth() == Month::FEBRUARY);
	REQUIRE(date1.GetDay() == 20);

	date1 -= (-10);
	REQUIRE(date1.GetMonth() == Month::MARCH);
	REQUIRE(date1.GetDay() == 1);

	date1 -= 366;
	REQUIRE(date1.GetMonth() == Month::MARCH);
	REQUIRE(date1.GetDay() == 1);
	REQUIRE(date1.GetYear() == 1999);

	CDate date2(31, Month::DECEMBER, 9999);
	date2 -=(-1);
	REQUIRE(date2.GetDay() == 1);
	REQUIRE(date2.GetYear() == 1970);
	REQUIRE(date2.GetMonth() == Month::JANUARY);

	CDate date3(31, Month::JANUARY, 1970);
	date3 -= 60;
	REQUIRE(date3.GetDay() == 1);
	REQUIRE(date3.GetYear() == 1970);
	REQUIRE(date3.GetMonth() == Month::JANUARY);
}

TEST_CASE("input")
{
	CDate date;

	SECTION("valid")
	{
		std::istringstream iss("25.04.2026");

		REQUIRE(iss >> date);
		REQUIRE(CDate::IsValid(date.GetDay(), date.GetMonth(), date.GetYear()));
		REQUIRE(date.GetDay() == 25);
		REQUIRE(date.GetMonth() == Month::APRIL);
		REQUIRE(date.GetYear() == 2026);
	}

	SECTION("valid and str after valid")
	{
		std::istringstream iss("25.04.2026 temp");

		REQUIRE(iss >> date);
		REQUIRE(CDate::IsValid(date.GetDay(), date.GetMonth(), date.GetYear()));

		std::string leftover;
		iss >> leftover;
		REQUIRE(leftover == "temp");
	}

	SECTION("invalid")
	{
		std::istringstream iss("25/04/2026");
		REQUIRE_FALSE(iss >> date);
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);

		iss.clear();
		iss.str("25.04-2026");
		REQUIRE_FALSE(iss >> date);
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);

		iss.clear();
		iss.str("qw.er.tyui");
		REQUIRE_FALSE(iss >> date);
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);

		iss.clear();
		iss.str("25.04");
		REQUIRE_FALSE(iss >> date);
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);
	}

	SECTION("incorect data")
	{
		std::istringstream iss("25.13.2026");
		REQUIRE_FALSE(iss >> date);
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);

		iss.clear();
		iss.str("32.01.2026");
		REQUIRE_FALSE(iss >> date);
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);

		iss.clear();
		iss.str("31.04.2026");
		REQUIRE_FALSE(iss >> date);
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);

		iss.clear();
		iss.str("29.02.2026");
		REQUIRE_FALSE(iss >> date);
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);
	}
}

TEST_CASE("output")
{
	CDate date;
	std::istringstream iss;
	std::ostringstream oss;

	SECTION("valid")
	{
		iss.clear();
		iss.str("25.04.2026");
		iss >> date;

		REQUIRE(oss << date);
		REQUIRE(oss.str() == "25.04.2026");
	}

	SECTION("invalid data")
	{
		iss.clear();
		iss.str("25.13.2026");
		iss >> date;
		REQUIRE(oss << date);
		REQUIRE(oss.str() == "INVALID");
		oss.str("");

		iss.clear();
		iss.str("32.01.2026");
		iss >> date;
		REQUIRE(oss << date);
		REQUIRE(oss.str() == "INVALID");
		oss.str("");

		iss.clear();
		iss.str("31.04.2026");
		iss >> date;
		REQUIRE(oss << date);
		REQUIRE(oss.str() == "INVALID");
		oss.str("");

		iss.clear();
		iss.str("29.02.2026");
		iss >> date;
		REQUIRE(oss << date);
		REQUIRE(oss.str() == "INVALID");
		oss.str("");
	}
}

TEST_CASE("bool operations")
{
	SECTION("equel")
	{
		CDate date1(25, Month::APRIL, 2026);
		CDate date2(25, Month::APRIL, 2026);
		CDate date3(25, Month::FEBRUARY, 2026);
		CDate date4(100, Month::FEBRUARY, 2026);

		REQUIRE(date1 == date2);
		REQUIRE(date2 == date1);

		REQUIRE_FALSE(date1 == date3);
		REQUIRE_FALSE(date2 == date3);

		REQUIRE_FALSE(date1 == date4);
		REQUIRE_FALSE(date2 == date4);
		REQUIRE_FALSE(date3 == date4);
		REQUIRE_FALSE(date4 == date4);
	}

	SECTION("not equel")
	{
		CDate date1(25, Month::APRIL, 2026);
		CDate date2(25, Month::APRIL, 2026);
		CDate date3(25, Month::FEBRUARY, 2026);
		CDate date4(100, Month::FEBRUARY, 2026);

		REQUIRE_FALSE(date1 != date2);
		REQUIRE_FALSE(date2 != date1);

		REQUIRE(date1 != date3);
		REQUIRE(date2 != date3);

		REQUIRE(date1 != date4);
		REQUIRE(date2 != date4);
		REQUIRE(date3 != date4);
		REQUIRE(date4 != date4);
	}

	SECTION("<")
	{
		CDate date1(25, Month::APRIL, 2026);
		CDate date2(25, Month::FEBRUARY, 2026);
		CDate date3(100, Month::FEBRUARY, 2026);

		REQUIRE_FALSE(date1 < date2);
		REQUIRE(date2 < date1);
		REQUIRE_FALSE(date1 < date1);
		REQUIRE_FALSE(date2 < date2);

		REQUIRE_FALSE(date1 < date3);
		REQUIRE_FALSE(date2 < date3);
		REQUIRE_FALSE(date3 < date1);
		REQUIRE_FALSE(date3 < date3);
	}

	SECTION(">")
	{
		CDate date1(25, Month::APRIL, 2026);
		CDate date2(25, Month::FEBRUARY, 2026);
		CDate date3(100, Month::FEBRUARY, 2026);

		REQUIRE(date1 > date2);
		REQUIRE_FALSE(date2 > date1);
		REQUIRE_FALSE(date1 > date1);
		REQUIRE_FALSE(date2 > date2);

		REQUIRE_FALSE(date1 > date3);
		REQUIRE_FALSE(date2 > date3);
		REQUIRE_FALSE(date3 > date1);
		REQUIRE_FALSE(date3 > date3);
	}

	SECTION("<=")
	{
		CDate date1(25, Month::APRIL, 2026);
		CDate date2(25, Month::FEBRUARY, 2026);
		CDate date3(100, Month::FEBRUARY, 2026);

		REQUIRE_FALSE(date1 <= date2);
		REQUIRE(date2 <= date1);
		REQUIRE(date1 <= date1);
		REQUIRE(date2 <= date2);

		REQUIRE_FALSE(date1 <= date3);
		REQUIRE_FALSE(date2 <= date3);
		REQUIRE_FALSE(date3 <= date1);
		REQUIRE_FALSE(date3 <= date1);
		REQUIRE_FALSE(date3 <= date3);
	}

	SECTION(">=")
	{
		CDate date1(25, Month::APRIL, 2026);
		CDate date2(25, Month::FEBRUARY, 2026);
		CDate date3(100, Month::FEBRUARY, 2026);

		REQUIRE(date1 >= date2);
		REQUIRE_FALSE(date2 >= date1);
		REQUIRE(date1 >= date1);
		REQUIRE(date2 >= date2);

		REQUIRE_FALSE(date1 >= date3);
		REQUIRE_FALSE(date2 >= date3);
		REQUIRE_FALSE(date3 >= date1);
		REQUIRE_FALSE(date3 >= date3);
	}
}