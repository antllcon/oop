#include "SubWordFinder/SubWordFinder.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>

using namespace std::chrono;

std::vector<std::string> ReadDictionary(const std::string& fileName)
{
	std::ifstream in{ fileName };
	std::string word;
	std::set<std::string> dictionarySet;

	while (getline(in, word))
	{
		if (!word.empty())
		{
			dictionarySet.emplace_hint(dictionarySet.end(), word);
		}
	}

	return { dictionarySet.begin(), dictionarySet.end() };
}

SubWords GetSubWords(const std::string& word, const SubWordFinder& finder)
{
	return finder.GetSubWords(word);
}

int main()
{
	try
	{
#if 1
		auto dictionary = ReadDictionary("dict.txt");
#else
		std::vector<std::string> dictionary = {
			"telega", "lemma", "gramm", "tema", "telo", "gamma"
		};
#endif
		const auto startTime = steady_clock::now();
		SubWordFinder finder(dictionary);
		const auto precompulationDuration = steady_clock::now() - startTime;

		std::cout << "Cоздали стркуктуру за: "
				  << duration<double>(precompulationDuration).count() << "с."
				  << std::endl;

		std::string searchWord = "gamma";
		const auto startProccess = steady_clock::now();
		auto subWords = GetSubWords(searchWord, finder);
		const auto proccessDuration = steady_clock::now() - startProccess;

		for (const auto& subWord : subWords)
		{
			std::cout << subWord << std::endl;
		}

		std::cout << subWords.size() << " слов найдено за "
				  << duration<double>(proccessDuration).count() << "с."
				  << std::endl;
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}