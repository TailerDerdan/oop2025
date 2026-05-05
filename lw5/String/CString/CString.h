#pragma once
#include <string>

class CString
{
public:
	CString();
	CString(const char* pString);
	CString(const char* pString, size_t length);
	CString(CString const& other);
	CString(CString && other) noexcept;
	CString(std::string const& stlString);
	~CString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();
	size_t GetCapacity() const;

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	CString& operator=(CString other);

	CString operator+(const CString& other) const;
	CString operator+(const std::string& other) const;
	CString operator+(const char* other) const;

	CString operator+=(const CString& other);

	bool operator==(const CString& other) const;
	std::partial_ordering operator<=>(const CString& other) const;

	friend std::ostream& operator<<(std::ostream& stream, const CString& other);
	friend std::istream& operator>>(std::istream& stream, CString& other);

	char operator*() const;

	using Iterator = char*;
	using ConstIterator = const char*;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	Iterator begin() noexcept { return m_data; }
	Iterator end() noexcept { return m_data + m_len; }

	ConstIterator begin() const noexcept { return m_data; }
	ConstIterator end() const noexcept { return m_data + m_len; }

	ConstIterator сbegin() const noexcept { return begin(); }
	ConstIterator cend() const noexcept { return end(); }

	ReverseIterator rbegin() noexcept { return ReverseIterator(end()); }
	ReverseIterator rend() noexcept { return ReverseIterator(begin()); }

	ConstReverseIterator rbegin() const noexcept { return ConstReverseIterator(end()); }
	ConstReverseIterator rend() const noexcept { return ConstReverseIterator(begin()); }

	ConstReverseIterator crbegin() const noexcept { return rbegin(); }
	ConstReverseIterator crend() const noexcept { return rend(); }

private:
	CString(const char* data, size_t length, size_t capacity);
	void PushBack(char c);

	char* m_data;
	size_t m_cap;
	size_t m_len;
};
