#include "SubWordFinder.hpp"
#include <array>
#include <fstream>

namespace
{
LettersMap MakeLetterMap(const std::string& word)
{
	LettersMap map{};

	for (char ch : word)
	{
		if (ch >= 'a' && ch <= 'z')
		{
			map[ch - 'a']++;
		}
	}

	return map;
}
} // namespace

SubWordFinder::SubWordFinder(const std::vector<std::string>& dictionary)
{
	m_precomputedDictionary.reserve(dictionary.size());

	for (const std::string& word : dictionary)
	{
		m_precomputedDictionary.push_back({ word, MakeLetterMap(word) });
	}
}

SubWords SubWordFinder::GetSubWords(const std::string& word) const
{
	SubWords result;
	LettersMap wordLettersMap = MakeLetterMap(word);

	for (const auto& dict_entry : m_precomputedDictionary)
	{
		if (IsForm(dict_entry.letterMap, wordLettersMap))
		{
			result.insert(dict_entry.word);
		}
	}

	return result;
}

IsForm(const LettersMap& subWordMap, const LettersMap& mainWordMap)
{
	for (int i = 0; i < constants::ENG_LETTERS; ++i)
	{
		if (subWordMap[i] > mainWordMap[i])
		{
			return false;
		}
	}

	return true;
}