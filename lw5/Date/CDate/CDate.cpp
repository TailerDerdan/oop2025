#include "CDate.h"

#include <array>
#include <iomanip>
#include <map>
#include <iostream>

constexpr long long SECONDS_IN_DAY = 86400;
constexpr long long DAYS_IN_YEAR = 365;
constexpr long long MONTHS_IN_YEAR = 12;
constexpr long long DAYS_IN_WEEK = 7;
constexpr long long MIN_YEAR = 1970;
constexpr long long MAX_YEAR = 9999;

constexpr long long DAYS_BETWEEN_1970_AND_0000 = 719468;
constexpr long long DAYS_IN_400_YEARS = 146097;
constexpr long long DAYS_IN_4_YEARS = 1460;
constexpr long long DAYS_IN_100_YEARS = 36524;
constexpr long long YEAR_IN_ERA = 400;
constexpr long long DAYS_IN_5_MONTH = 153;

constexpr unsigned long MAX_TIMESTAMP = 253402300799;

static constexpr std::array<Month, MONTHS_IN_YEAR> months = {
	Month::JANUARY, Month::FEBRUARY, Month::MARCH, Month::APRIL,
	Month::MAY, Month::JUNE, Month::JULY, Month::AUGUST,
	Month::SEPTEMBER, Month::OCTOBER, Month::NOVEMBER, Month::DECEMBER
};

static constexpr std::array<WeekDay, DAYS_IN_WEEK> weeks = {
	WeekDay::SUNDAY, WeekDay::MONDAY, WeekDay::TUESDAY, WeekDay::WEDNESDAY, WeekDay::THURSDAY,
	WeekDay::FRIDAY, WeekDay::SATURDAY
};

static const std::map<WeekDay, std::string> nameWeeks = {
	{WeekDay::MONDAY, "monday"}, {WeekDay::TUESDAY, "tuesday"}, {WeekDay::WEDNESDAY, "wednesday"},
	{WeekDay::THURSDAY, "thursday"},{WeekDay::FRIDAY, "friday"}, {WeekDay::SATURDAY, "saturday"},
	{WeekDay::SUNDAY, "sunday"}
};

static const std::map<Month, unsigned> numberMonths = {
	{Month::JANUARY, 1}, {Month::FEBRUARY, 2}, {Month::MARCH, 3}, {Month::APRIL, 4},
	{Month::MAY, 5}, {Month::JUNE, 6}, {Month::JULY, 7}, {Month::AUGUST, 8},
	{Month::SEPTEMBER, 9}, {Month::OCTOBER, 10}, {Month::NOVEMBER, 11}, {Month::DECEMBER, 12}
};

static const std::map<Month, std::string> nameMonths = {
	{Month::JANUARY, "january"}, {Month::FEBRUARY, "february"}, {Month::MARCH, "march"}, {Month::APRIL, "april"},
	{Month::MAY, "may"}, {Month::JUNE, "june"}, {Month::JULY, "july"}, {Month::AUGUST, "august"},
	{Month::SEPTEMBER, "september"}, {Month::OCTOBER, "october"}, {Month::NOVEMBER, "november"}, {Month::DECEMBER, "december"}
};

static const std::map<Month, unsigned> daysMonths = {
	{Month::JANUARY, 31}, {Month::FEBRUARY, 28}, {Month::MARCH, 31}, {Month::APRIL, 30},
	{Month::MAY, 31}, {Month::JUNE, 30}, {Month::JULY, 31}, {Month::AUGUST, 31},
	{Month::SEPTEMBER, 30}, {Month::OCTOBER, 31}, {Month::NOVEMBER, 30}, {Month::DECEMBER, 31}
};

CDate::CDate()
{
	m_timestamp = 0;
	m_isValid = true;
}

CDate::CDate(Timestamp timestamp)
{
	if (timestamp > MAX_TIMESTAMP)
	{
		m_timestamp = 0;
		m_isValid = false;
		return;
	}
	m_timestamp = timestamp;
	m_isValid = true;
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (!IsValid(day, month, year))
	{
		m_timestamp = 0;
		m_isValid = false;
		return;
	}
	const auto monthNum = numberMonths.find(month)->second;
	signed yearSigned = year - (monthNum <= 2);
	const int era = (yearSigned >= 0 ? yearSigned : yearSigned - (YEAR_IN_ERA - 1)) / YEAR_IN_ERA;
	const unsigned yearInEra = yearSigned - era * YEAR_IN_ERA;
	const unsigned monthInEra = (monthNum > 2) ? (monthNum - 3) : (monthNum + 9);
	const unsigned dayInEra = yearInEra * DAYS_IN_YEAR + yearInEra / 4 - yearInEra / 100 + (DAYS_IN_5_MONTH * monthInEra + 2) / 5 + day - 1;
	m_timestamp = (era * DAYS_IN_400_YEARS + dayInEra - DAYS_BETWEEN_1970_AND_0000) * SECONDS_IN_DAY;
	m_isValid = true;
}

unsigned CDate::GetDay() const
{
	auto timeValues = GetTimeValues(m_timestamp);
	return (timeValues.dayInYear - (DAYS_IN_5_MONTH * timeValues.monthShifted + 2) / 5 + 1);
}

Month CDate::GetMonth() const
{
	auto timeValues = GetTimeValues(m_timestamp);
	unsigned month = timeValues.monthShifted < 10 ? timeValues.monthShifted + 3 : timeValues.monthShifted - 9;
	return GetMonth(month);
}

unsigned CDate::GetYear() const
{
	auto timeValues = GetTimeValues(m_timestamp);
	unsigned month = timeValues.monthShifted < 10 ? timeValues.monthShifted + 3 : timeValues.monthShifted - 9;
	return static_cast<unsigned>(timeValues.year + (month <= 2 ? 1 : 0));
}

WeekDay CDate::GetWeekDay() const
{
	unsigned days = m_timestamp / SECONDS_IN_DAY;
	return weeks[(days + 4) % DAYS_IN_WEEK];
}

bool CDate::IsValid(unsigned day, Month month, unsigned year)
{
	if (bool leap = IsLeapYear(year); day < 1 || day > GetDayOfMonth(month, leap))
	{
		return false;
	}

	if (year < MIN_YEAR || year > MAX_YEAR)
	{
		return false;
	}

	return true;
}

Month CDate::GetMonth(unsigned month)
{
	return months[month - 1];
}

unsigned CDate::GetNumberMonth(Month month)
{
	return numberMonths.find(month)->second;
}

unsigned CDate::GetDayOfMonth(Month month, bool isLeapYear)
{
	return month == Month::FEBRUARY && isLeapYear ? daysMonths.at(month) + 1 : daysMonths.at(month);
}

std::string CDate::GetMonthName() const
{
	return nameMonths.at(GetMonth());
}

std::string CDate::GetWeekName() const
{
	return nameWeeks.at(GetWeekDay());
}

TimeValuesDTO CDate::GetTimeValues(Timestamp timestamp)
{
	Timestamp days = timestamp / SECONDS_IN_DAY;

	long daysFrom0000 = static_cast<long>(days) + DAYS_BETWEEN_1970_AND_0000;
	long era = (daysFrom0000 >= 0 ? daysFrom0000 : daysFrom0000 - DAYS_IN_400_YEARS + 1) / DAYS_IN_400_YEARS;
	unsigned dayInEra = daysFrom0000 - era * DAYS_IN_400_YEARS;
	unsigned yearInEra = (dayInEra - dayInEra / DAYS_IN_4_YEARS + dayInEra / DAYS_IN_100_YEARS - dayInEra / (DAYS_IN_400_YEARS - 1)) / DAYS_IN_YEAR;
	int year = static_cast<int>(yearInEra) + era * YEAR_IN_ERA;
	unsigned dayInYear = dayInEra - (DAYS_IN_YEAR * yearInEra + yearInEra / 4 - yearInEra / 100);
	unsigned monthShifted = (5 * dayInYear + 2) / DAYS_IN_5_MONTH;

	TimeValuesDTO timeValues{};
	timeValues.year = year;
	timeValues.dayInYear = dayInYear;
	timeValues.monthShifted = monthShifted;
	return timeValues;
}

bool CDate::IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

CDate CDate::operator++(int)
{
	if (!m_isValid) return *this;

	CDate temp = *this;
	++(*this);

	if (!IsValid(temp.GetDay(), temp.GetMonth(), temp.GetYear()))
	{
		m_isValid = false;
		m_timestamp = 0;
		return *this;
	}

	return temp;
}

CDate& CDate::operator++()
{
	if (!m_isValid) return *this;

	m_timestamp += SECONDS_IN_DAY;

	if (!IsValid(GetDay(), GetMonth(), GetYear()))
	{
		m_isValid = false;
		m_timestamp = 0;
		return *this;
	}

	return *this;
}

CDate CDate::operator--(int)
{
	if (!m_isValid) return *this;

	CDate temp = *this;
	--(*this);

	if (!IsValid(temp.GetDay(), temp.GetMonth(), temp.GetYear()))
	{
		m_isValid = false;
		m_timestamp = 0;
		return *this;
	}

	return temp;
}
CDate& CDate::operator--()
{
	if (!m_isValid) return *this;

	m_timestamp -= SECONDS_IN_DAY;

	if (!IsValid(GetDay(), GetMonth(), GetYear()))
	{
		m_isValid = false;
		m_timestamp = 0;
		return *this;
	}

	return *this;
}

CDate CDate::operator+(int days) const
{
	if (!m_isValid) return *this;
	CDate result(*this);
	result.m_timestamp += days * SECONDS_IN_DAY;
	if (!IsValid(result.GetDay(), result.GetMonth(), result.GetYear()))
	{
		result.m_timestamp = 0;
		result.m_isValid = false;
		return result;
	}
	return result;
}

CDate CDate::operator-(int days) const
{
	if (!m_isValid) return *this;
	CDate result(*this);
	result.m_timestamp -= days * SECONDS_IN_DAY;
	if (!IsValid(result.GetDay(), result.GetMonth(), result.GetYear()))
	{
		result.m_isValid = false;
		result.m_timestamp = 0;
		return result;
	}
	return result;
}

int CDate::operator-(const CDate& other) const
{
	if (!this->m_isValid || !other.m_isValid) return 0;
	const signed result = signed(this->m_timestamp) - signed(other.m_timestamp);
	return result / SECONDS_IN_DAY;
}

CDate operator+(int days, const CDate& date)
{
	return date + days;
}

CDate& CDate::operator+=(int days)
{
	if (!m_isValid) return *this;
	m_timestamp = m_timestamp + days * SECONDS_IN_DAY;
	if (!IsValid(GetDay(), GetMonth(), GetYear()))
	{
		m_isValid = false;
		m_timestamp = 0;
	}
	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (!m_isValid) return *this;
	m_timestamp = m_timestamp - days * SECONDS_IN_DAY;
	if (!IsValid(GetDay(), GetMonth(), GetYear()))
	{
		m_isValid = false;
		m_timestamp = 0;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const CDate& other)
{
	if (!other.m_isValid)
	{
		stream << "INVALID";
		return stream;
	}
	stream << std::setfill('0')
			<< std::setw(2) << other.GetDay() << '.'
			<< std::setw(2) << CDate::GetNumberMonth(other.GetMonth()) << '.'
			<< std::setw(4) << other.GetYear();
	return stream;
}

std::istream& operator>>(std::istream& stream, CDate& other)
{
	unsigned day, monthNum, year;
	char dot1, dot2;

	if (stream >> day >> dot1 >> monthNum >> dot2 >> year)
	{
		if (dot1 == '.' && dot2 == '.' && monthNum >= 1 && monthNum <= MONTHS_IN_YEAR)
		{
			CDate temp(day, CDate::GetMonth(monthNum), year);
			if (temp.m_isValid)
			{
				other = temp;
				return stream;
			}
		}
	}
	other.m_isValid = false;
	stream.clear(std::ios::failbit);
	return stream;
}

// реализовать через spaceship

bool CDate::operator==(const CDate& other) const
{
	if (!this->m_isValid || !other.m_isValid) return false;
	return this->m_timestamp == other.m_timestamp;
}

std::partial_ordering CDate::operator<=>(const CDate& other) const
{
	if (!m_isValid || !other.m_isValid) return std::partial_ordering::unordered;
	return m_timestamp <=> other.m_timestamp;
}