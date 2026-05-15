#pragma once
#include <iterator>

#include "Node.h"

template <bool isConst>
class IteratorStringListBase
{
	using Reference = std::conditional_t<isConst, const std::string&, std::string&>;
	using Pointer = std::conditional_t<isConst, const std::string*, std::string*>;
	using NodePtr = std::conditional_t<isConst, const Node*, Node*>;

	NodePtr m_border;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::string;
	using difference_type = std::ptrdiff_t;
	using reference = Reference;
	using pointer = Pointer;

	explicit IteratorStringListBase(NodePtr node, NodePtr border) : m_node(node), m_border(border) {}

	template <bool wasConst, typename = std::enable_if_t<isConst || !wasConst>>
	IteratorStringListBase(const IteratorStringListBase<wasConst>& other) : m_node(other.m_node), m_border(other.m_border) {}

	reference operator*() const
	{
		if (m_node == m_border)
		{
			throw std::out_of_range("can not dereference end() iterator");
		}

		return m_node->data;
	}

	pointer operator->() const
	{
		if (m_node == m_border)
		{
			throw std::out_of_range("can not dereference end() iterator");
		}
		return &m_node->data;
	}

	IteratorStringListBase& operator++()
	{
		if (m_node == m_border)
		{
			throw std::out_of_range("can not increment end()");
		}
		m_node = m_node->next ? m_node->next.get() : m_border;
		return *this;
	}
	IteratorStringListBase operator++(int) { auto tmp = *this; ++(*this); return tmp; }

	IteratorStringListBase& operator--()
	{
		if (m_node->prev == m_border)
		{
			throw std::out_of_range("can not decrement begin()");
		}
		m_node = m_node->prev;
		return *this;
	}
	IteratorStringListBase operator--(int) { auto tmp = *this; --(*this); return tmp; }

	bool operator==(const IteratorStringListBase& rhs) const { return m_node == rhs.m_node; }
	bool operator!=(const IteratorStringListBase& rhs) const { return !(*this == rhs); }

private:
	NodePtr m_node;
	template <bool> friend class IteratorStringListBase;
	friend class StringList;
};
