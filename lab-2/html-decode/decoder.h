#ifndef DECODER_H
#define DECODER_H

#include <sstream>
#include <string>

void CopyStreamWithHtmlDecode(std::istream& input, std::ostream& output);
std::string HtmlDecode(const std::string& html);

#endif