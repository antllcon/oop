#include <array>
#include <cstdint>
#include <string>
#include <unordered_set>
#include <vector>

namespace constants
{
inline constexpr size_t ENG_LETTERS = 26;
}

using LettersMap = std::array<uint8_t, constants::ENG_LETTERS>;
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
	std::vector<WordInfo> m_precomputedDictionary;
};