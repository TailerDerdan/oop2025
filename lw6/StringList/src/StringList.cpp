#include "StringList.h"

StringList::StringList()
{
	m_head = std::make_unique<Node>();
	m_head->next = nullptr;
	m_head->prev = m_head.get();
	m_size = 0;
}

StringList::StringList(std::initializer_list<std::string> items) : StringList()
{
	for (const auto& item : items)
	{
		push_back(item);
	}
}

StringList::StringList(const StringList& list) : StringList()
{
	for (const auto& item : list)
	{
		push_back(item);
	}
}

StringList::StringList(StringList&& list) noexcept
	: m_head(std::move(list.m_head))
	, m_size(list.m_size)
{
	list.m_head = std::make_unique<Node>();
	list.m_head->next = nullptr;
	list.m_head->prev = m_head.get();
	list.m_size = 0;
}

StringList& StringList::operator=(StringList list)
{
	std::swap(m_head, list.m_head);
	std::swap(m_size, list.m_size);
	return *this;
}


StringList::~StringList() noexcept
{
	clear();
}

void StringList::push_back(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data);
	auto newRaw = newNode.get();
	Node* last = m_head->prev;
	newNode->next = nullptr;
	newNode->prev = last;
	last->next = std::move(newNode);
	m_head->prev = newRaw;
	++m_size;
}

void StringList::push_front(const std::string& data)
{
	if (m_size == 0)
	{
		push_back(data);
	}
	else
	{
		auto newNode = std::make_unique<Node>(data);
		auto first = std::move(m_head->next);
		auto firstRaw = first.get();
		newNode->next = std::move(first);
		newNode->prev = m_head.get();
		firstRaw->prev = newNode.get();
		m_head->next = std::move(newNode);
		++m_size;
	}
}

std::string StringList::pop_back()
{
	if (empty())
	{
		throw std::out_of_range("pop_back() called on empty StringList");
	}
	auto prevLast = m_head->prev->prev;
	std::string result = std::move(m_head->prev->data);
	prevLast->next = nullptr;
	m_head->prev = prevLast;
	m_size--;
	return result;
}

std::string StringList::pop_front()
{
	if (empty())
	{
		throw std::out_of_range("pop_front() called on empty StringList");
	}
	auto firstRaw = m_head->next.get();
	auto result = std::move(firstRaw->data);
	m_head->next = std::move(firstRaw->next);
	if (m_head->next)
	{
		m_head->next->prev = m_head.get();
	}
	else
	{
		m_head->prev = m_head.get();
	}
	m_size--;
	return result;
}

void StringList::clear()
{
	while (m_head->next != nullptr)
	{
		m_head->next = std::move(m_head->next->next);
	}
	m_head->prev = m_head.get();
	m_size = 0;
}

size_t StringList::size() const
{
	return m_size;
}

bool StringList::empty() const
{
	return m_size == 0;
}

void StringList::Insert(const std::string& data, ConstIterator pos)
{
	if (pos == cbegin())
	{
		push_front(data);
		return;
	}

	if (pos == cend())
	{
		push_back(data);
		return;
	}

	Node* nextNode = const_cast<Node*>(pos.m_node);
	Node* prevNode = nextNode->prev;

	auto newNode = std::make_unique<Node>(data);
	Node* newRaw = newNode.get();

	newNode->next = std::move(prevNode->next);
	newNode->prev = prevNode;
	prevNode->next = std::move(newNode);
	nextNode->prev = newRaw;
	m_size++;
}

StringList::Iterator StringList::Delete(ConstIterator pos)
{
	if (pos == cend())
	{
		throw std::out_of_range("can not delete end iterator");
	}

	if (pos == cbegin())
	{
		pop_front();
		return begin();
	}

	if (pos == (--cend()))
	{
		pop_back();
		return end();
	}

	auto prevRaw = const_cast<Node*>(pos.m_node->prev);
	auto nextRaw = const_cast<Node*>(pos.m_node->next.get());

	prevRaw->next = std::move(nextRaw->prev->next);
	nextRaw->prev = prevRaw;

	m_size--;
	return Iterator(nextRaw, m_head.get());
}