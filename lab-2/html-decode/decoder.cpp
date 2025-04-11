#include "decoder.h"
#include <unordered_map>

const std::unordered_map<std::string_view, char> HTML_ENTITIES = {
	{ "&quot;", '\"' },
	{ "&apos;", '\'' },
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' },
};

void CopyStreamWithHtmlDecode(std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		std::string decodeString = HtmlDecode(line);
		output << decodeString << std::endl;
	}
}

std::string HtmlDecode(const std::string& html)
{
	std::string decodeLine;
	for (size_t i = 0; i < html.size(); i++)
	{
		size_t semicolonPos = html.find(';', i);
		if (html[i] != '&' || semicolonPos == std::string::npos)
		{
			decodeLine += html[i];
			continue;
		}

		std::string_view htmlEntity(&html[i], semicolonPos - i + 1);
		auto htmlCh = HTML_ENTITIES.find(htmlEntity);
		if (htmlCh == HTML_ENTITIES.end())
		{
			decodeLine += html[i];
			continue;
		}
		decodeLine += htmlCh->second;
		i += semicolonPos - i;
	}
	return decodeLine;
}