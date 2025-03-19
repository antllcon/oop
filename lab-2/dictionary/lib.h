#include <iostream>
#include <set>
#include <unordered_map>

using ListWords = std::set<std::string>;
using Dictionary = std::unordered_map<std::string, ListWords>;

/// @brief Получение имени файла из входного потока данных
/// @param argc количество аргументов входного потока
/// @param argv аргументы входного потока
/// @return Возвращает имя файла или завершается исключением
std::string GetFileName(int argc, char* argv[]);

/// @brief Получение словаря из файла
/// @param fileName имя файла словаря
/// @return Возвращает структуру словаря из файла или завершается исключением
Dictionary GetDictionary(const std::string& fileName);

/// @brief Процесс диалога с пользователем для получения перевода слов или обновления словаря
/// @param dictionary структура словаря
/// @param fileName имя файла словаря (для сохранения измнений)
void ProcessDialog(Dictionary& dictionary, const std::string& fileName);

// Вывод перевода в теорминал
void PrintTranslation(ListWords& translation);

// Нормализация строки (TrimWord + ToLower)
std::string Normalize(const std::string& input);

// Приведение строки к нижнему регистру
std::string ToLower(const std::string& str);

// Конвертация wstring к utf-8 (глупые кодировки)
std::string WstringToUtf8(const std::wstring& wstr);

// Конвертация utf-8 к wstring (глупые кодировки)
std::wstring Utf8ToWstring(const std::string& str);

// Получение перевода введеного слова
ListWords GetTranslation(Dictionary& dictionary, std::string line);

// Перезаписывание словаря в файл
void RewriteDictionary(std::ofstream& file, Dictionary& dictionary);

// Запрос у пользователя на сохранение изменений
bool SaveQuestion(void);

// Провека состояния потока ввода
void CheckIstream(std::istream& cin);

// Сохранение словаря в файл, если были внесены изменения
void SaveDictionary(const std::string& fileName, Dictionary& dictionary, bool modified);

// Получение строки от пользователя
std::string GetMessage(std::istream&);

// Добавление перевода слова; если пользователь вводит несколько вариантов через запятую,
// они разбиваются и для каждого создаётся обратное соответствие.
void AddTranslation(Dictionary& dictionary, std::string word, bool& modified);

// Удаление пробелов в начале и конце строки
std::string TrimWord(const std::string& word);

// Разбиение строки с переводами
ListWords SplitString(const std::string& line);

// Получение набора переводов из строки после разделителя
ListWords GetDictionaryLineValues(const std::string& line);

// Получение ключевой фразы из строки словаря
std::string GetDictionaryLineWord(const std::string& line);

// Поиск разделителя в строке; если не найден – генерация исключения
size_t FindSeparator(const std::string& line, const std::string& key);