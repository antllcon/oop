#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "dictionary.h"
#include <algorithm>
#include <codecvt>
#include <fstream>
#include <locale>
#include <ranges>

std::string GetFileName(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error("Не правильно переданы аргументы");
	}
	return argv[1];
}

Dictionary GetDictionary(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return {};
	}

	Dictionary dictionary;
	std::string line;

	while (std::getline(file, line))
	{
		std::string word = Normalize(GetDictionaryLineWord(line));
		ListWords translation = GetDictionaryLineValues(line);
		dictionary[word] = translation;
	}

	return dictionary;
}

std::string GetDictionaryLineWord(const std::string& line)
{
	size_t separatorPos = FindSeparator(line, " - ");
	return line.substr(0, separatorPos);
}

size_t FindSeparator(const std::string& line, const std::string& key)
{
	size_t pos = line.find(key);
	if (pos == std::string::npos)
	{
		throw std::runtime_error("Некорректный формат строки (" + line + ") словаря.");
	}
	return pos;
}

ListWords GetDictionaryLineValues(const std::string& line)
{
	constexpr int SEP_SIZE = 3;
	size_t pos = FindSeparator(line, " - ");
	std::string translationsStr = line.substr(pos + SEP_SIZE);
	return SplitString(translationsStr);
}

ListWords SplitString(const std::string& line)
{
	ListWords words;
	size_t start = 0;
	size_t end = line.find(", ");

	while (end != std::string::npos)
	{
		std::string word = TrimWord(line.substr(start, end - start));
		if (!word.empty())
		{
			words.insert(word);
		}
		start = end + 2;
		end = line.find(", ", start);
	}

	std::string word = TrimWord(line.substr(start));
	if (!word.empty())
	{
		words.insert(word);
	}
	if (words.empty())
	{
		throw std::runtime_error("Нехватает перевода слова в строке (" + line + ").");
	}
	return words;
}

std::string TrimWord(const std::string& word)
{
	if (word.empty())
	{
		return "";
	}

	size_t start = word.find_first_not_of(' ');
	if (start == std::string::npos)
	{
		return "";
	}

	size_t end = word.find_last_not_of(' ');
	return word.substr(start, end - start + 1);
}

void ProcessDialog(Dictionary& dictionary, const std::string& fileName)
{
	bool modified = false;

	while (true)
	{
		std::string userMessage = GetMessage(std::cin);
		if (userMessage == "...")
		{
			SaveDictionary(fileName, dictionary, modified);
			break;
		}
		ListWords translation = GetTranslation(dictionary, userMessage);
		if (translation.empty())
		{
			HandleTranslationWord(dictionary, userMessage, modified);
		}
		else
		{
			PrintTranslation(translation);
		}
	}
}

void HandleTranslationWord(Dictionary& dictionary, std::string& word, bool& modified)
{
	std::cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку.\n";
	std::string translationLine;
	CheckIstream(std::cin);
	std::getline(std::cin, translationLine);
	translationLine = TrimWord(translationLine);

	if (translationLine.empty())
	{
		std::cout << "Слово \"" << word << "\" проигнорировано.\n";
		return;
	}

	if (AddTranslation(dictionary, word, translationLine))
	{
		std::cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translationLine
				  << "\".\n";
		modified = true;
	}
}

bool AddTranslation(Dictionary& dictionary, std::string& word, std::string& translationLine)
{
	ListWords translations = SplitString(translationLine);
	for (std::string translation : translations)
	{
		dictionary[word].insert(translationLine);
		dictionary[translation].insert(word);
	}
	return true;
}

std::string GetMessage(std::istream&)
{
	std::string line;
	std::cout << ">";
	if (!(std::cin.fail() || std::cin.bad()))
	{
		std::getline(std::cin, line);
	}
	return line;
}

void SaveDictionary(const std::string& fileName, Dictionary& dictionary, bool modified)
{
	if (!modified)
	{
		std::cout << "Изменения сохранены." << std::endl;
		return;
	}

	if (!SaveQuestion())
	{
		std::cout << "Изменения не сохранены." << std::endl;
		return;
	}

	std::ofstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Невозможно сохраненить файл.");
	}

	RewriteDictionary(file, dictionary);
	std::cout << "Изменения сохранены." << std::endl;
}

void CheckIstream(std::istream& cin)
{
	if (cin.fail() || cin.bad())
	{
		throw std::runtime_error("Проблемы с входным потоком");
	}
}

bool SaveQuestion(void)
{
	std::cout << "Вы хотите сохранить файл? (y/n)\n";
	CheckIstream(std::cin);

	std::string line;
	std::getline(std::cin, line);
	return TrimWord(line) == "y" || TrimWord(line) == "Y";
}

void RewriteDictionary(std::ofstream& file, Dictionary& dictionary)
{
	for (const auto& [word, translations] : dictionary)
	{
		file << word << " - ";
		bool first = true;
		for (const auto& translation : translations)
		{
			if (!first)
				file << ", ";
			file << translation;
			first = false;
		}
		file << std::endl;
	}
}

ListWords GetTranslation(Dictionary& dictionary, std::string line)
{
	std::string lowerLine = Normalize(line);
	for (const auto& [key, translations] : dictionary)
	{
		if (Normalize(key) == lowerLine)
		{
			return translations;
		}
	}

	return {};
}

std::string ToLower(const std::string& str)
{
	std::wstring wstr = Utf8ToWstring(str);
	for (wchar_t& ch : wstr)
	{
		ch = std::towlower(ch);
	}
	return WstringToUtf8(wstr);
}

std::string WstringToUtf8(const std::wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wstr);
}

std::wstring Utf8ToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}

std::string Normalize(const std::string& input) { return ToLower(TrimWord(input)); }

void PrintTranslation(ListWords& translation)
{
	for (std::string value : translation)
	{
		std::cout << value << std::endl;
	}
}

#endif