// sub_words.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm> // Для std::sort
#include <array> // Для std::array в TrieNode
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory> // Для std::unique_ptr
#include <set>
#include <string>
#include <unordered_set> // Используем unordered_set для более быстрой вставки
#include <vector>

using namespace std;

// --- Начало высокопроизводительного решения ---

// Узел в нашем Trie
struct TrieNode
{
	// Массив указателей на дочерние узлы. 'a' -> 0, 'b' -> 1, ...
	array<unique_ptr<TrieNode>, 26> children;
	// Список оригинальных слов, которые соответствуют этому пути (канонической форме)
	vector<string> words;

	TrieNode()
		: children()
	{
	} // Инициализация гарантирует, что все указатели будут nullptr
};

// Класс для инкапсуляции логики построения Trie и поиска
class SubWordFinder
{
public:
	// Конструктор принимает словарь и строит Trie
	SubWordFinder(const vector<string>& dictionary)
	{
		root = make_unique<TrieNode>();
		for (const string& word : dictionary)
		{
			add_word_to_trie(word);
		}
	}

	// Основной метод для поиска слов
	unordered_set<string> getSubWords(const string& word) const
	{
		unordered_set<string> result;
		string sorted_word = word;
		sort(sorted_word.begin(), sorted_word.end());

		// Запускаем рекурсивный поиск
		search(root.get(), sorted_word, 0, result);
		return result;
	}

private:
	unique_ptr<TrieNode> root;

	void add_word_to_trie(const string& word)
	{
		string sorted_word = word;
		sort(sorted_word.begin(), sorted_word.end());

		TrieNode* current = root.get();
		for (char ch : sorted_word)
		{
			int index = ch - 'a';
			if (!current->children[index])
			{
				current->children[index] = make_unique<TrieNode>();
			}
			current = current->children[index].get();
		}
		current->words.push_back(word);
	}

	// Рекурсивная функция поиска
	void search(const TrieNode* node, const string& sorted_word, int start_index, unordered_set<string>& result) const
	{
		// Если текущий узел содержит слова, добавляем их в результат
		if (!node->words.empty())
		{
			result.insert(node->words.begin(), node->words.end());
		}

		// Пробуем расширить путь, используя буквы из sorted_word, начиная со start_index
		for (int i = start_index; i < sorted_word.length(); ++i)
		{
			// Оптимизация: если текущий символ такой же, как предыдущий,
			// мы его уже обработали в предыдущей итерации цикла. Пропускаем.
			// Это критически важно для слов с повторяющимися буквами.
			if (i > start_index && sorted_word[i] == sorted_word[i - 1])
			{
				continue;
			}

			char ch = sorted_word[i];
			int index = ch - 'a';
			if (node->children[index])
			{
				// Если есть дочерний узел для этой буквы, продолжаем поиск вглубь
				search(node->children[index].get(), sorted_word, i + 1, result);
			}
		}
	}
};

// --- Старый код для контекста ---

vector<string> ReadDictionary(const string& file_name)
{
	ifstream in{ file_name };
	string word;
	// Используем set для автоматического удаления дубликатов и сортировки
	set<string> dictionary_set;
	while (getline(in, word))
	{
		if (!word.empty())
		{
			// emplace_hint - небольшая оптимизация для вставки в set
			dictionary_set.emplace_hint(dictionary_set.end(), word);
		}
	}
	return { dictionary_set.begin(), dictionary_set.end() };
}

/*
 * Исходная функция, которую мы заменяем классом SubWordFinder.
 * Мы можем сделать ее оберткой для нашего класса.
 */
unordered_set<string> GetSubWords(const string& word, const SubWordFinder& finder) { return finder.getSubWords(word); }

int main()
{
	using namespace std;
	using namespace std::chrono;

#if 1 // Включаем чтение из файла для реального теста
	cout << "Reading dictionary..." << endl;
	auto dictionary = ReadDictionary("dict.txt"); // Убедитесь, что файл dict.txt существует
	cout << "Dictionary contains " << dictionary.size() << " words." << endl;
#else
	vector<string> dictionary = { "telega"s, "lemma"s, "gramm"s, "tema"s, "telo"s, "gamma"s, "eat"s, "tea"s, "ate"s };
#endif

	// --- Этап 1: Предварительная обработка ---
	cout << "\nBuilding search structure (Trie)..." << endl;
	const auto precomputation_start_time = steady_clock::now();
	SubWordFinder finder(dictionary);
	const auto precomputation_dur = steady_clock::now() - precomputation_start_time;
	cout << "Structure built in "sv << duration<double>(precomputation_dur).count() << " seconds" << endl;

	// --- Этап 2: Поиск ---
	// string search_word = "gammatelo"; // Для тестового словаря
	string search_word = "trustfulness"; // Слово из оригинального примера
	cout << "\nSearching for sub-words of \"" << search_word << "\"..." << endl;

	const auto start_time = steady_clock::now();
	const auto sub_words = GetSubWords(search_word, finder);
	const auto dur = steady_clock::now() - start_time;

	for (const auto& sub_word : sub_words)
	{
		std::cout << sub_word << std::endl;
	}

	std::cout << "\n"
			  << sub_words.size() << " words have been found in "sv << duration<double>(dur).count() << " seconds"
			  << std::endl;

	return 0;
}