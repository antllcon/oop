#include "../dictionary.h"
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

TEST(GetDictionaryTest, Test)
{
	std::string fileName = "dict";
	GetDictionary(fileName);
}