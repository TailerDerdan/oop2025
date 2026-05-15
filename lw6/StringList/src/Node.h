#pragma once

#include <iostream>
#include <string>
#include <memory>

struct Node
{
	std::string data;
	std::unique_ptr<Node> next;
	Node* prev = nullptr;
};