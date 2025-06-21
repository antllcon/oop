#include <array>
#include <cstdint>
#include <string>
#include <unordered_set>
#include <vector>

using LettersMap = std::array<uint8_t, 26>;
using SubWords = std::unordered_set<std::string>;

struct WordInfo
{
	std::string word;
	LettersMap letterMap;
};

class SubWordFinder
{
public:
	SubWordFinder(const std::vector<std::string>& dictionary);
	SubWords GetSubWords(const std::string& word) const;

private:
	bool IsForm(
		const LettersMap& subWordMap, const LettersMap& mainWordMap) const;

	std::vector<WordInfo> m_precomputedDictionary;
};