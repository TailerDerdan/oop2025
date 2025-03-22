#pragma once

#include <string>
#include <optional>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	Invalid
};

struct URL
{
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;
};

//���������� � optional
std::optional<URL> ParseURL(const std::string& url);