#pragma once

#include "IteratorStringList.h"

class StringList
{
public:
	StringList();
	StringList(std::initializer_list<std::string> items);
	StringList(const StringList& list);
	StringList(StringList&& list) noexcept;
	StringList& operator=(StringList list);
	~StringList() noexcept;

	void push_back(const std::string& data);
	void push_front(const std::string& data);
	std::string pop_back();
	std::string pop_front();
	void clear();
	size_t size() const;
	bool empty() const;

	using Iterator = IteratorStringListBase<false>;
	using ConstIterator = IteratorStringListBase<true>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	Iterator begin() noexcept { return Iterator(m_head->next ? m_head->next.get() : m_head.get(), m_head.get()); }
	Iterator end() noexcept { return Iterator(m_head.get(), m_head.get()); }

	ConstIterator begin() const noexcept { return ConstIterator(m_head->next ? m_head->next.get() : m_head.get(), m_head.get()); }
	ConstIterator end() const noexcept { return ConstIterator(m_head.get(), m_head.get()); }

	ConstIterator cbegin() const noexcept { return begin(); }
	ConstIterator cend() const noexcept { return end(); }

	ReverseIterator rbegin() noexcept { return ReverseIterator(end()); }
	ReverseIterator rend() noexcept { return ReverseIterator(begin()); }

	ConstReverseIterator rbegin() const noexcept { return ConstReverseIterator(end()); }
	ConstReverseIterator rend() const noexcept { return ConstReverseIterator(begin()); }

	ConstReverseIterator crbegin() const noexcept { return rbegin(); }
	ConstReverseIterator crend() const noexcept { return rend(); }

	void Insert(const std::string& data, ConstIterator pos);
	Iterator Delete(ConstIterator pos);

private:
	std::unique_ptr<Node> m_head = nullptr;
	size_t m_size = 0;
};