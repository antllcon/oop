#ifndef HTTP_URL_H
#define HTTP_URL_H

#include "Protocol.h"
#include <ostream>
#include <stdexcept>
#include <string>

struct UrlParsingError : std::invalid_argument
{
	UrlParsingError(std::string message)
		: std::invalid_argument(std::move(message))
	{
	}
};

using Port = unsigned short;

class HttpUrl
{
public:
	explicit HttpUrl(const std::string& url);

	explicit HttpUrl(
		const std::string& domain,
		const std::string& document,
		Protocol protocol = Protocol::HTTP);

	explicit HttpUrl(
		const std::string& domain,
		const std::string& document,
		Protocol protocol,
		Port port);

	std::string GetUrl() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	Port GetPort() const;

	friend std::ostream& operator<<(std::ostream& out, const HttpUrl& url);

private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
};

#endif // HTTP_URL_H