#include "../decoder.h"
#include <gtest/gtest.h>
#include <sstream>

// Корректные сущности
TEST(TryDecodeHtmlEntityTests, DecodesValidEntity)
{
	std::string decoded;
	EXPECT_TRUE(TryDecodeHtmlEntity("&quot;", 0, 5, decoded));
	EXPECT_EQ(decoded, "\"");

	decoded.clear();
	EXPECT_TRUE(TryDecodeHtmlEntity("&amp;", 0, 4, decoded));
	EXPECT_EQ(decoded, "&");
}

// Не корректные сущности
TEST(TryDecodeHtmlEntityTests, FailsForInvalidEntity)
{
	std::string decoded;
	EXPECT_FALSE(TryDecodeHtmlEntity("&invalidus;", 0, 10, decoded));
	EXPECT_EQ(decoded, "");

	EXPECT_FALSE(TryDecodeHtmlEntity("&anonymus", 0, 9, decoded));
	EXPECT_EQ(decoded, "");
}

// Ошибочные сущности (отсутствует точка с запятой)
TEST(TryDecodeHtmlEntityTests, HandlesPartialEntity)
{
	std::string decoded;
	EXPECT_FALSE(TryDecodeHtmlEntity("&amp", 0, 3, decoded));
	EXPECT_EQ(decoded, "");
}

// Пустая сущность
TEST(TryDecodeHtmlEntityTests, HandlesEmptyInput)
{
	std::string decoded;
	EXPECT_FALSE(TryDecodeHtmlEntity("", 0, 0, decoded));
	EXPECT_EQ(decoded, "");
}

// Сущность начинающаяся около слова
TEST(TryDecodeHtmlEntityTests, HandlesEntityAtNonZeroPosition)
{
	std::string decoded = "prefix";
	EXPECT_TRUE(TryDecodeHtmlEntity("prefix&quot;", 6, 11, decoded));
	EXPECT_EQ(decoded, "prefix\"");
}

// Проверка мапы
TEST(HtmlDecodeTests, DecodesSingleHtmlEntity)
{
	EXPECT_EQ(HtmlDecode("&quot;"), "\"");
	EXPECT_EQ(HtmlDecode("&apos;"), "'");
	EXPECT_EQ(HtmlDecode("&lt;"), "<");
	EXPECT_EQ(HtmlDecode("&gt;"), ">");
	EXPECT_EQ(HtmlDecode("&amp;"), "&");
}

// Проверка декодирования нескольких сущностей
TEST(HtmlDecodeTests, DecodesMultipleHtmlEntities)
{
	EXPECT_EQ(HtmlDecode("&lt;div&gt;Hello &amp; Welcome&lt;/div&gt;"),
		"<div>Hello & Welcome</div>");
	EXPECT_EQ(HtmlDecode("&quot;Test&quot; &apos;String&apos;"), "\"Test\" 'String'");
}

// Проверка декодирования текста с ложными сущностями
TEST(HtmlDecodeTests, IgnoresInvalidHtmlEntities)
{
	EXPECT_EQ(HtmlDecode("&sus;"), "&sus;");
	EXPECT_EQ(HtmlDecode("&amogus"), "&amogus");
	EXPECT_EQ(HtmlDecode("text&amogus;text"), "text&amogus;text");
}

// Проверка декодирования текста с некорректными сущностями
TEST(HtmlDecodeTests, HandlesMixedValidAndInvalidEntities)
{
	EXPECT_EQ(HtmlDecode("&lt;div&gt;mama: &yanaoop;&lt;/div&gt;"),
		"<div>mama: &yanaoop;</div>");
}

// Пустой текст (не текст по идее)
TEST(HtmlDecodeTests, HandlesEmptyString) { EXPECT_EQ(HtmlDecode(""), ""); }

// Проверка декодирования текста без сущностей и с цифрами
TEST(HtmlDecodeTests, HandlesStringWithoutEntities)
{
	EXPECT_EQ(HtmlDecode("abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz");
	EXPECT_EQ(HtmlDecode("0123456789"), "0123456789");
}

// Проверка декодирования текста с амперсандами
TEST(HtmlDecodeTests, HandlesStringWithOnlyAmpersand)
{
	EXPECT_EQ(HtmlDecode("&"), "&");
	EXPECT_EQ(HtmlDecode("&&"), "&&");
}