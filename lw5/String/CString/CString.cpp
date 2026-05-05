#include "CString.h"
#include <algorithm>
#include <fstream>

namespace
{
	char* AllocateMemory(size_t size)
	{
		return new char[size]();
	}
}

CString::CString() : m_len(0), m_cap(1), m_data(AllocateMemory(1))
{
	m_data[0] = '\0';
}

CString::CString(const char* pString) : CString(pString, strlen(pString))
{
}

//поправить утечку памяти с std::memcpy
CString::CString(const char* pString, size_t length) : m_len(length), m_cap(length + 1), m_data(AllocateMemory(length + 1))
{
	if (pString && m_len > 0)
	{
		std::memcpy(m_data, pString, m_len);
	}

	m_data[m_len] = '\0';
}

CString::CString(CString const& other) : CString(other.m_data, other.m_len, other.m_cap)
{
}

CString::CString(CString && other) noexcept : CString(other.m_data, other.m_len, other.m_cap)
{
	other.m_data = nullptr;
	other.m_len = 0;
	other.m_cap = 0;
}

CString::CString(std::string const& stlString) : CString(stlString.c_str(), stlString.length())
{
}

CString::~CString()
{
	delete[] m_data;
}

size_t CString::GetLength() const
{
	return m_len;
}

const char* CString::GetStringData() const
{
	return m_data;
}

CString CString::SubString(size_t start, size_t length) const
{
	if (start >= m_len || start + length > m_len)
	{
		throw std::out_of_range("start > length of string");
	}
	size_t currentLen = std::min(length, m_len - start);
	return {m_data + start, currentLen};
}

void CString::Clear()
{
	delete[] m_data;
	m_data = AllocateMemory(1);
	m_len = 0;
	m_cap = 1;
	m_data[0] = '\0';
}

size_t CString::GetCapacity() const
{
	return m_cap;
}

char& CString::operator[](size_t index)
{
	if (index >= m_len)
	{
		throw std::out_of_range("index out of range");
	}
	return m_data[index];
}

const char& CString::operator[](size_t index) const
{
	if (index >= m_len)
	{
		throw std::out_of_range("index out of range");
	}
	return m_data[index];
}

CString& CString::operator=(CString other)
{
	std::swap(m_data, other.m_data);
	std::swap(m_len, other.m_len);
	std::swap(m_cap, other.m_cap);
	return *this;
}

CString CString::operator+(const CString& other) const
{
	CString result(*this);
	result += other;
	return result;
}

CString CString::operator+(const std::string& other) const
{
	return *this + CString(other);
}

CString CString::operator+(const char* other) const
{
	return *this + CString(other);
}

//может произойти утечка памяти
CString CString::operator+=(const CString& other)
{
	auto newLen = m_len + other.m_len;
	if (newLen + 1 > m_cap)
	{
		m_cap = std::max(m_cap * 2, newLen + 1);
		auto newData = AllocateMemory(m_cap);

		if (m_data && newLen > 0)
		{
			std::memcpy(newData, m_data, newLen);
		}

		delete[] m_data;
		m_data = newData;
	}
	if (other.m_data && other.m_len > 0)
	{
		std::memcpy(m_data + m_len, other.m_data, other.m_len);
	}

	m_len = newLen;
	m_data[m_len] = '\0';
	return *this;
}

//разобраться со spaceship
bool CString::operator==(const CString& other) const
{
	return m_len == other.m_len && std::equal(m_data, m_data + m_len, other.m_data);
}

std::partial_ordering CString::operator<=>(const CString& other) const
{
	size_t minLen = std::min(m_len, other.m_len);
	int cmp = std::memcmp(m_data, other.m_data, minLen);

	if (cmp < 0) return std::partial_ordering::less;
	if (cmp > 0) return std::partial_ordering::greater;

	return m_len <=> other.m_len;
}

std::ostream& operator<<(std::ostream& stream, const CString& other)
{
	if (other.m_data)
	{
		stream << other.GetStringData();
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, CString& other)
{
	other.Clear();
	char ch;

	while (stream.get(ch) && std::isspace(ch)) {}

	if (!stream) return stream;

	do
	{
		other.PushBack(ch);
	} while (stream.get(ch) && !std::isspace(ch));

	if (stream)
	{
		stream.unget();
	}

	return stream;
}



CString::CString(const char* data, size_t length, size_t capacity) : m_len(length), m_cap(capacity), m_data(nullptr)
{
	if (data)
	{
		m_data = AllocateMemory(m_cap);
		std::memcpy(m_data, data, m_len + 1);
	}
}

//утечка памяти из-за ошибки memcpy
void CString::PushBack(char c)
{
	if (m_len + 1 >= m_cap)
	{
		m_cap = std::max(m_cap * 2, m_len + 2);
		auto newData = AllocateMemory(m_cap);

		if (m_data && m_len > 0)
		{
			std::memcpy(newData, m_data, m_len);
		}

		delete[] m_data;
		m_data = newData;
	}
	m_data[m_len] = c;
	m_len++;
	m_data[m_len] = '\0';
}