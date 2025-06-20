#include "ParseUrl.h"
#include <algorithm>
#include <regex>
#include <stdexcept>
#include <unordered_map>

using namespace parse_url;

namespace constants
{
inline constexpr int MIN_PORT = 1;
inline constexpr int MAX_PORT = 65535;
} // namespace constants

const std::unordered_map<std::string, Protocol> PROTOCOL_MAP = {
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS },
	{ "ftp", Protocol::FTP }
};

const std::unordered_map<Protocol, int> PROTOCOL_DEFAULT_PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 }
};

std::string ToLower(const std::string& str)
{
	std::string result(str.size(), '\0');

	std::transform(str.begin(), str.end(), result.begin(),
		[](const char ch) { return static_cast<char>(std::tolower(ch)); });

	return result;
}

Protocol ParseProtocol(const std::string& protocolStr)
{
	auto it = PROTOCOL_MAP.find(ToLower(protocolStr));
	if (it == PROTOCOL_MAP.end())
	{
		throw std::runtime_error("Неизвестный протокол: " + protocolStr);
	}
	return it->second;
}

int ParsePort(const std::string& portStr, Protocol protocol)
{
	if (portStr.empty())
	{
		auto it = PROTOCOL_DEFAULT_PORT.find(protocol);
		if (it == PROTOCOL_DEFAULT_PORT.end())
		{
			throw std::runtime_error("Не удалось найти стандартный порт");
		}
		return it->second;
	}

	int port = std::stoi(portStr);
	AssertIsPortInRange(port);

	return port;
}

bool parse_url::ParseURL(const std::string& url, UrlData& data)
{
	UrlData temp = data;
	auto& [protocol, host, port, document] = temp;

	try
	{
		std::regex urlRegex(R"(^([a-zA-Z]+):\/\/([a-zA-Z0-9\.\-]+)(?::([0-9]{1,5}))?(?:\/([^?#\s]*))?(?:\?([^#\s]*))?(?:#(\S*))?$)", std::regex::icase);
		// std::regex urlRegex(R"(^([a-zA-Z]+):\/\/([a-zA-Z0-9\.\-]+)(?::([0-9]{1,5}))?(\/[^\?#\s]*)?(?:\?[^\#\$]*)?(?:\#[^\$]*)?$)", std::regex::icase);
		// std::regex urlRegex(R"(^([a-zA-Z]+):\/\/([a-zA-Z0-9\.-]+)(?::([0-9]+))?(\/[^?#\s]*)?(?:\?[^#\s]*)?(?:#[^\s]*)?$)", std::regex::icase);

		std::smatch match;
		if (!std::regex_match(url, match, urlRegex))
		{
			throw std::runtime_error("Регулярное выражение не выполнилось");
		}

		protocol = ParseProtocol(match[1]);
		host = match[2];
		port = ParsePort(match[3], protocol);
		document = match[4].matched ? match[4].str() : "";
		data = temp;
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

void parse_url::AssertIsPortInRange(int port)
{
	if (port < constants::MIN_PORT || port > constants::MAX_PORT)
	{
		throw std::runtime_error("Порт должен быть в диапазоне от "
			+ std::to_string(constants::MIN_PORT) + " и до " + std::to_string(constants::MAX_PORT));
	}
}