#include "HttpUrl.h"
#include "ParseUrl.h"
#include <fmt/format.h>
#include <unordered_map>

// Правки:
// 1. Вынести в константу localhost

namespace
{
constexpr const char* DEFAULT_PORT_FORMAT = "{}://{}/{}";
constexpr const char* CUSTOM_PORT_FORMAT = "{}://{}:{}/{}";
constexpr const char* DEFAULT_DOMAIN = "localhost";

std::unordered_map<Protocol::Enum, Port> PROTOCOL_TO_DEFAULT_PORT = {
	{ Protocol::HTTP, Port(80) },
	{ Protocol::HTTPS, Port(443) }
};

bool IsPortDefault(Protocol protocol, Port port)
{
	if (auto it = PROTOCOL_TO_DEFAULT_PORT.find(protocol); it != PROTOCOL_TO_DEFAULT_PORT.end())
	{
		return port == it->second;
	}
	return false;
}
} // namespace

HttpUrl::HttpUrl(const std::string& url)
{
	parse_url::UrlData data;
	if (!parse_url::ParseURL(url, data) || data.protocol == parse_url::Protocol::FTP)
	{
		throw UrlParsingError("Ошибка парсинга URL");
	}

	m_protocol = data.protocol == parse_url::Protocol::HTTP ? Protocol::HTTP : Protocol::HTTPS;
	m_domain = data.host;
	m_document = data.document;
	m_port = static_cast<Port>(data.port);
}

HttpUrl::HttpUrl(
	const std::string& domain,
	const std::string& document,
	Protocol protocol)
	: HttpUrl(domain, document, protocol, PROTOCOL_TO_DEFAULT_PORT[protocol])
{
}

HttpUrl::HttpUrl(
	const std::string& domain,
	const std::string& document,
	Protocol protocol,
	Port port)
	: m_domain(domain.empty() ? DEFAULT_DOMAIN : domain)
	, m_document(document)
	, m_protocol(protocol)
	, m_port(port)
{
	parse_url::AssertIsPortInRange(static_cast<int>(port));
}

std::string HttpUrl::GetUrl() const
{
	if (IsPortDefault(m_protocol, m_port))
	{
		return fmt::format(DEFAULT_PORT_FORMAT, m_protocol.ToString(), m_domain, m_document);
	}

	return fmt::format(CUSTOM_PORT_FORMAT, m_protocol.ToString(), m_domain, m_port, m_document);
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

Port HttpUrl::GetPort() const
{
	return m_port;
}

std::ostream& operator<<(std::ostream& out, const HttpUrl& url)
{
	return out << url.GetUrl();
}