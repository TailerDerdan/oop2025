#include "ParseUrlModules.h"
#include <regex>
#include <optional>
#include <map>

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

//переделать в const
const std::map<std::string, int> PORT_BY_PROTOCOL = { { "http", 80 }, { "https", 443 }, { "ftp", 21 } };
const std::map<std::string, Protocol> PROTOCOL_BY_STR = { { "http", Protocol::HTTP }, { "https", Protocol::HTTPS }, { "ftp", Protocol::FTP } };

std::string StrTolower(const std::string& s)
{
	std::string result = s;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

std::optional<int> GetDefaultPortByProtocol(const std::string& protocolStr)
{
	auto port = PORT_BY_PROTOCOL.find(protocolStr);
	if (port != PORT_BY_PROTOCOL.end())
	{
		return port->second;
	}
	return std::nullopt;
}

Protocol GetProtocolByString(const std::string& protocolStr)
{
	auto protocol = PROTOCOL_BY_STR.find(protocolStr);
	if (protocol != PROTOCOL_BY_STR.end())
	{
		return protocol->second;
	}
	return Protocol::Invalid;
}

std::optional<int> GetPort(const std::string& protocolStr, const std::smatch& urlMatch)
{
	int port = 0;
	if (!urlMatch[4].str().empty())
	{
		port = std::stoi(urlMatch[4].str());
		if (port < MIN_PORT || port > MAX_PORT)
		{
			return std::nullopt;
		}
		return port;
	}
	auto portByProtocol = GetDefaultPortByProtocol(protocolStr);
	if (!portByProtocol)
	{
		return std::nullopt;
	}
	port = portByProtocol.value();
	return port;
}

std::string GetDocument(const std::smatch& urlMatch)
{
	std::string document;
	if (!urlMatch[5].str().empty())
	{
		document.append(urlMatch[5].str(), 1, urlMatch[5].str().size() - 1);
	}
	return document;
}

std::optional<URL> ParseURL(const std::string& url)
{
	URL urlParams;
	std::string urlLowerCase = StrTolower(url);
	std::regex urlRegex(R"(((https?|ftp):\/\/)([^\/:]+)(?::(\d+))?(\/\S*)?)");

	std::smatch urlMatch;

	if (std::regex_match(urlLowerCase, urlMatch, urlRegex))
	{
		std::string protocolStr = urlMatch[2].str();
		urlParams.host = urlMatch[3].str();

		urlParams.protocol = GetProtocolByString(protocolStr);
		if (urlParams.protocol == Protocol::Invalid)
		{
			return std::nullopt;
		}
		auto port = GetPort(protocolStr, urlMatch);
		if (!port)
		{
			return std::nullopt;
		}
		urlParams.port = port.value();
		urlParams.document = GetDocument(urlMatch);
		
		return urlParams;
	}
	return std::nullopt;
}