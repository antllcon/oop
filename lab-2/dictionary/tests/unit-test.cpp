#include "../lib.h"
#include <gtest/gtest.h>

#include <codecvt>
#include <cstdio>
#include <fstream>
#include <locale>
#include <sstream>

// Проверка получения имени файла
TEST(GetFileNameTest, ValidArgs)
{
	char* argv[] = { (char*)"start", (char*)"dictionary" };
	int argc = 2;
	EXPECT_EQ(GetFileName(argc, argv), "dictionary");
}

// Не передано имя файла
TEST(GetFileNameTest, InvalidArgs)
{
	char* argv[] = { (char*)"start" };
	int argc = 1;
	EXPECT_THROW(GetFileName(argc, argv), std::runtime_error);
}

// Получение ключа
TEST(GetDictionaryLineWordTest, ExtractsKey)
{
	std::string line = "cat - кот, кошка";
	EXPECT_EQ(GetDictionaryLineWord(line), "cat");
}

// Поиск разделителя
TEST(FindSeparatorTest, FoundSeparator)
{
	std::string line = "cat - кот, кошка";
	size_t pos = FindSeparator(line, " - ");
	EXPECT_EQ(pos, 3);
}

// Отсутствие разделителя
TEST(FindSeparatorTest, NotFoundThrows)
{
	std::string line = "cat кот, кошка";
	EXPECT_THROW(FindSeparator(line, " - "), std::runtime_error);
}

// Проверка получения переводов
TEST(GetDictionaryLineValuesTest, ExtractsValues)
{
	std::string line = "cat - кот, кошка";
	ListWords values = GetDictionaryLineValues(line);
	EXPECT_EQ(values.size(), 2);
	EXPECT_NE(values.find("кот"), values.end());
	EXPECT_NE(values.find("кошка"), values.end());
}

//
TEST(SplitStringTest, MultipleValues)
{
	std::string input = "кот, кошка";
	ListWords words = SplitString(input);
	EXPECT_EQ(words.size(), 2);
	EXPECT_NE(words.find("кот"), words.end());
	EXPECT_NE(words.find("кошка"), words.end());
}

TEST(SplitStringTest, SingleValue)
{
	std::string input = "мяч";
	ListWords words = SplitString(input);
	EXPECT_EQ(words.size(), 1);
	EXPECT_NE(words.find("мяч"), words.end());
}

TEST(SplitStringTest, EmptyInputThrows)
{
	std::string input = "   ";
	EXPECT_THROW(SplitString(input), std::runtime_error);
}

TEST(TrimWordTest, TrimsSpaces)
{
	EXPECT_EQ(TrimWord("  hello  "), "hello");
	EXPECT_EQ(TrimWord("  hello"), "hello");
	EXPECT_EQ(TrimWord("hello  "), "hello");
	EXPECT_EQ(TrimWord("   "), "");
	EXPECT_EQ(TrimWord(""), "");
}

TEST(ProcessDialogTest, ExitImmediately)
{
	std::istringstream input("...\ny\n");
	auto origBuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());
	Dictionary dict;
	EXPECT_NO_THROW(ProcessDialog(dict, "testfile"));
	std::cin.rdbuf(origBuf);
}

TEST(AddTranslationTest, AddsTranslationCorrectly)
{
	// Симулируем ввод перевода "мясо" для слова "meat"
	std::istringstream input("мясо\n");
	auto origBuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());

	Dictionary dict;
	bool modified = false;
	AddTranslation(dict, "meat", modified);

	// Проверяем, что в словаре для ключа "meat" (как ввели) содержится введённый перевод
	EXPECT_NE(dict.find("meat"), dict.end());
	EXPECT_NE(dict["meat"].find("мясо"), dict["meat"].end());
	// Проверяем обратный перевод: ключ нормализованного "мясо" должен содержать "meat"
	std::string normalizedTranslation = Normalize("мясо");
	EXPECT_NE(dict.find(normalizedTranslation), dict.end());
	EXPECT_NE(dict[normalizedTranslation].find("meat"), dict[normalizedTranslation].end());

	std::cin.rdbuf(origBuf);
}

// ---------- Тестирование GetMessage ----------
TEST(GetMessageTest, ReturnsLine)
{
	std::istringstream input("hello world\n");
	auto origBuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());
	std::string msg = GetMessage(std::cin);
	EXPECT_EQ(msg, "hello world");
	std::cin.rdbuf(origBuf);
}

// ---------- Тестирование SaveDictionary ----------
// Создаем временной файл, записываем туда словарь и читаем содержимое
TEST(SaveDictionaryTest, WritesToFile)
{
	std::string filename = "temp_test_dict.txt";
	Dictionary dict;
	dict["cat"].insert("кошка");
	dict["cat"].insert("кот");
	bool modified = true;

	std::istringstream input("y\n");
	auto origBuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());

	SaveDictionary(filename, dict, modified);

	std::ifstream file(filename);
	std::stringstream ss;
	ss << file.rdbuf();
	std::string content = ss.str();
	EXPECT_NE(content.find("cat -"), std::string::npos);
	EXPECT_NE(content.find("кошка"), std::string::npos);
	EXPECT_NE(content.find("кот"), std::string::npos);

	file.close();
	std::remove(filename.c_str());
	std::cin.rdbuf(origBuf);
}

// ---------- Тестирование CheckIstream ----------
TEST(CheckIstreamTest, ValidStream)
{
	std::istringstream input("data");
	EXPECT_NO_THROW(CheckIstream(input));
}

TEST(CheckIstreamTest, InvalidStreamThrows)
{
	std::istringstream input("");
	input.setstate(std::ios::failbit);
	EXPECT_THROW(CheckIstream(input), std::runtime_error);
}

// ---------- Тестирование SaveQuestion ----------
TEST(SaveQuestionTest, AcceptsLowercaseY)
{
	std::istringstream input("y\n");
	auto origBuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());
	EXPECT_TRUE(SaveQuestion());
	std::cin.rdbuf(origBuf);
}

TEST(SaveQuestionTest, AcceptsUppercaseY)
{
	std::istringstream input("Y\n");
	auto origBuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());
	EXPECT_TRUE(SaveQuestion());
	std::cin.rdbuf(origBuf);
}

TEST(SaveQuestionTest, RejectsOtherInput)
{
	std::istringstream input("n\n");
	auto origBuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());
	EXPECT_FALSE(SaveQuestion());
	std::cin.rdbuf(origBuf);
}

TEST(GetTranslationTest, ReturnsCaseInsensitiveTranslations)
{
	Dictionary dict;
	dict["cat"].insert("кошка");
	dict["cat"].insert("кот");
	ListWords translations = GetTranslation(dict, "CAT");
	EXPECT_EQ(translations.size(), 2);
	EXPECT_NE(translations.find("кошка"), translations.end());
	EXPECT_NE(translations.find("кот"), translations.end());
}

TEST(ToLowerTest, ConvertsAsciiAndRussian)
{
	std::string input = "CaT";
	std::string lower = ToLower(input);
	EXPECT_EQ(lower, "cat");
}

TEST(UtfConversionTest, RoundTripConversion)
{
	std::string original = "Привет, мир!";
	std::wstring wstr = Utf8ToWstring(original);
	std::string utf8 = WstringToUtf8(wstr);
	EXPECT_EQ(utf8, original);
}

TEST(NormalizeTest, TrimsAndLowers)
{
	std::string input = "  CaT  ";
	std::string normalized = Normalize(input);
	EXPECT_EQ(normalized, "cat");
}

TEST(PrintTranslationTest, OutputsTranslations)
{
	ListWords translations;
	translations.insert("кошка");
	translations.insert("кот");
	std::ostringstream oss;
	auto origBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());
	PrintTranslation(translations);
	std::cout.rdbuf(origBuf);
	std::string output = oss.str();
	EXPECT_NE(output.find("кошка"), std::string::npos);
	EXPECT_NE(output.find("кот"), std::string::npos);
}
