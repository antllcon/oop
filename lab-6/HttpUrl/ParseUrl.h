#ifndef PARSE_URL_H
#define PARSE_URL_H

#include <string>

namespace parse_url
{
enum class Protocol
{
	UNKNOWN = 0,
	HTTP,
	HTTPS,
	FTP
};

struct UrlData
{
	Protocol protocol = Protocol::UNKNOWN;
	std::string host;
	int port = -1;
	std::string document;

	bool operator==(const UrlData& other) const
	{
		return protocol == other.protocol && host == other.host && port == other.port && document == other.document;
	}
};

bool ParseURL(const std::string& url, UrlData& data);
void AssertIsPortInRange(int port);

} // namespace parse_url

#endif // PARSE_URL_H