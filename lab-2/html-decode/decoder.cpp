#include "decoder.h"
#include <unordered_map>

const std::unordered_map<std::string_view, char> HTML_DECODE_MAP
	= { { "&quot;", '"' }, { "&apos;", '\'' }, { "&lt;", '<' }, { "&gt;", '>' },
		  { "&amp;", '&' } };

void CopyStreamWithHtmlDecode(std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		std::string decodeString = HtmlDecode(line);
		output << decodeString << std::endl;
	}
}

bool TryDecodeHtmlEntity(const std::string& text, size_t startPos,
	size_t semicolonPos, std::string& decodeLine)
{
	std::string_view htmlEntity(&text[startPos], semicolonPos - startPos + 1);
	auto htmlCh = HTML_DECODE_MAP.find(htmlEntity);
	if (htmlCh != HTML_DECODE_MAP.end())
	{
		decodeLine += htmlCh->second;
		return true;
	}
	return false;
}

std::string HtmlDecode(const std::string& text)
{
	std::string decodeLine;
	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] != '&')
		{
			decodeLine += text[i];
			continue;
		}

		size_t semicolonPos = text.find(';', i);
		if (semicolonPos == std::string::npos
			|| !TryDecodeHtmlEntity(text, i, semicolonPos, decodeLine))
		{
			decodeLine += text[i];
		}
		else
		{
			i = semicolonPos;
		}
	}
	return decodeLine;
}