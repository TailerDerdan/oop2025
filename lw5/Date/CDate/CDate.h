#pragma once

#include <string>

enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

struct TimeValuesDTO
{
	int year = 0;
	unsigned dayInYear = 0;
	unsigned monthShifted = 0;
};

using Timestamp = unsigned long long;

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);
	explicit CDate(Timestamp timestamp);
	CDate();

	unsigned GetDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;

	static bool IsValid(unsigned day, Month month, unsigned year);
	static unsigned GetNumberMonth(Month month);

	std::string GetMonthName() const;
	std::string GetWeekName() const;

	CDate operator++(int);
	CDate& operator++();

	CDate operator--(int);
	CDate& operator--();

	CDate operator+(int days) const;

	CDate operator-(int days) const;
	int operator-(const CDate& other) const;

	CDate& operator+=(int days);
	CDate& operator-=(int days);

	friend std::ostream& operator<<(std::ostream& stream, const CDate& other);
	friend std::istream& operator>>(std::istream& stream, CDate& other);

	bool operator==(const CDate& other) const;
	std::partial_ordering operator<=>(const CDate& other) const;

private:
	static TimeValuesDTO GetTimeValues(Timestamp timestamp);
	static Month GetMonth(unsigned month);
	static unsigned GetDayOfMonth(Month month, bool isLeapYear);
	static bool IsLeapYear(unsigned year);

private:
	Timestamp m_timestamp = 0;
	bool m_isValid = true;
};

CDate operator+(int days, const CDate& date);