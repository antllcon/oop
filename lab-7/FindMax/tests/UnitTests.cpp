#include "FindMaxEx.hpp"
#include <gtest/gtest.h>
#include <limits>

TEST(FindMaxExTest, EmptyVector)
{
	std::vector<int> emptyVec;
	int maxValue;
	EXPECT_FALSE(FindMaxEx(emptyVec, maxValue));
}

TEST(FindMaxExTest, SingleElement)
{
	std::vector<int> vec = { 42 };
	int maxValue;
	EXPECT_TRUE(FindMaxEx(vec, maxValue));
	EXPECT_EQ(maxValue, 42);
}

TEST(FindMaxExTest, IntVector)
{
	std::vector<int> vec = { 1, 5, 3, -2, 10, std::numeric_limits<int>::max() };
	int maxValue;
	EXPECT_TRUE(FindMaxEx(vec, maxValue));
	EXPECT_EQ(maxValue, std::numeric_limits<int>::max());
}

TEST(FindMaxExTest, CustomComparatorDescending)
{
	std::vector<int> vec = { 1, 5, 3, -2, 10, std::numeric_limits<int>::max() };
	int minValue;
	auto less = [](const int& a, const int& b) { return a > b; };
	EXPECT_TRUE(FindMaxEx(vec, minValue, less));
	EXPECT_EQ(minValue, -2);
}

TEST(FindMaxExTest, StringLengthComparator)
{
	std::vector<std::string> vec = { "a", "abc", "ab", "abcd" };
	std::string maxValue;
	auto less = [](const std::string& a, const std::string& b) {
		return a.length() < b.length();
	};
	EXPECT_TRUE(FindMaxEx(vec, maxValue, less));
	EXPECT_EQ(maxValue, "abcd");
}
TEST(FindMaxExTest, DataIntegrityAfterFindMax)
{
	struct Person
	{
		std::string name;
		int age;

		Person(const std::string& n, int a)
			: name(n)
			, age(a)
		{
		}

		Person& operator=(const Person& other)
		{
			if (other.age < 0)
			{
				throw std::runtime_error("assign error");
			}

			name = other.name;
			age = other.age;
			return *this;
		}
	};

	const std::vector<Person> originalVec = {
		{ "Илья", 25 },
		{ "Влад", 30 },
		{ "Степан", 20 }
	};

	std::vector<Person> vec = originalVec;
	Person maxValue("", 0);
	auto ageCompare = [](const Person& a, const Person& b) {
		return a.age < b.age;
	};

	EXPECT_NO_THROW(FindMaxEx(vec, maxValue, ageCompare));

	EXPECT_EQ(vec.size(), originalVec.size());
	for (size_t i = 0; i < vec.size(); ++i)
	{
		EXPECT_EQ(vec[i].name, originalVec[i].name);
		EXPECT_EQ(vec[i].age, originalVec[i].age);
	}

	EXPECT_TRUE(FindMaxEx(vec, maxValue, ageCompare));
	EXPECT_EQ(maxValue.name, "Влад");
	EXPECT_EQ(maxValue.age, 30);
}

TEST(FindMaxExTest, ExceptionOnInvalidAssignment)
{
	struct Person
	{
		std::string name;
		int age;

		Person(const std::string& n, int a)
			: name(n)
			, age(a)
		{
		}

		Person& operator=(const Person& other)
		{
			if (other.age < 0)
			{
				throw std::runtime_error("assign error");
			}

			name = other.name;
			age = other.age;
			return *this;
		}
	};

	const std::vector<Person> originalVec = {
		{ "Илья", 25 },
		{ "Влад", 30 },
		{ "Степан", -1 }
	};

	std::vector<Person> vec = originalVec;
	Person minValue("", 0);
	auto ageCompare = [](const Person& a, const Person& b) {
		return a.age > b.age;
	};

	const auto vecBefore = vec;
	const auto minValueBefore = minValue;

	EXPECT_THROW(FindMaxEx(vec, minValue, ageCompare), std::runtime_error);

	EXPECT_EQ(vec.size(), originalVec.size());
	for (size_t i = 0; i < vec.size(); ++i)
	{
		EXPECT_EQ(vec[i].name, originalVec[i].name);
		EXPECT_EQ(vec[i].age, originalVec[i].age);
	}

	EXPECT_EQ(minValue.name, minValueBefore.name);
	EXPECT_EQ(minValue.age, minValueBefore.age);
}

// Добавить тест на выкидыаение исключени