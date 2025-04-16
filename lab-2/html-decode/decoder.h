#ifndef DECODER_H
#define DECODER_H

#include <sstream>
#include <string>

void CopyStreamWithHtmlDecode(std::istream& input, std::ostream& output);
bool TryDecodeHtmlEntity(const std::string& text, size_t startPos,
	size_t semicolonPos, std::string& decodeLine);
std::string HtmlDecode(const std::string& html);

#endif