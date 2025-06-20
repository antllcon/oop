#include "Vector.hpp"
#include <gtest/gtest.h>
#include <numeric>
#include <string>
#include <vector>

// Класс для проверки вызовов конструктора/деструктора
struct Counter
{
	static int constructions;
	static int destructions;

	Counter() { ++constructions; }
	Counter(const Counter&) { ++constructions; }
	Counter(Counter&&) noexcept { ++constructions; }
	~Counter() { ++destructions; }

	Counter& operator=(const Counter&) = default;
	Counter& operator=(Counter&&) noexcept = default;
};

int Counter::constructions = 0;
int Counter::destructions = 0;

TEST(VectorTest, DefaultConstructor)
{
	Vector<int> vec;
	EXPECT_EQ(vec.GetSize(), 0);
}

TEST(VectorTest, PushBackAndAccess)
{
	Vector<int> vec;
	vec.PushBack(10);
	vec.PushBack(20);
	EXPECT_EQ(vec.GetSize(), 2);
	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 20);
}

TEST(VectorTest, PushBackMove)
{
	Vector<std::string> vec;
	std::string str = "hello";
	vec.PushBack(std::move(str));
	EXPECT_EQ(vec[0], "hello");
}

TEST(VectorTest, EmplaceBack)
{
	Vector<std::pair<int, std::string>> vec;
	vec.EmplaceBack(1, "abc");
	EXPECT_EQ(vec[0].first, 1);
	EXPECT_EQ(vec[0].second, "abc");
}

TEST(VectorTest, PopBack)
{
	Vector<int> vec;
	vec.PushBack(1);
	vec.PushBack(2);
	vec.PopBack();
	EXPECT_EQ(vec.GetSize(), 1);
	EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, ResizeIncrease)
{
	Vector<int> vec;
	vec.Resize(5);
	EXPECT_EQ(vec.GetSize(), 5);
	for (int i = 0; i < 5; ++i)
		vec[i] = i;
	EXPECT_EQ(vec[4], 4);
}

TEST(VectorTest, ResizeDecrease)
{
	Vector<int> vec;
	for (int i = 0; i < 5; ++i)
		vec.PushBack(i);
	vec.Resize(2);
	EXPECT_EQ(vec.GetSize(), 2);
	EXPECT_EQ(vec[1], 1);
}

TEST(VectorTest, CopyConstructor)
{
	Vector<int> vec;
	vec.PushBack(1);
	vec.PushBack(2);
	Vector<int> copy = vec;
	EXPECT_EQ(copy.GetSize(), 2);
	EXPECT_EQ(copy[0], 1);
	EXPECT_EQ(copy[1], 2);
}

TEST(VectorTest, CopyAssignment)
{
	Vector<int> vec;
	vec.PushBack(3);
	Vector<int> copy;
	copy = vec;
	EXPECT_EQ(copy.GetSize(), 1);
	EXPECT_EQ(copy[0], 3);
}

TEST(VectorTest, MoveConstructor)
{
	Vector<int> vec;
	vec.PushBack(1);
	Vector<int> moved = std::move(vec);
	EXPECT_EQ(moved.GetSize(), 1);
	EXPECT_EQ(moved[0], 1);
}

TEST(VectorTest, MoveAssignment)
{
	Vector<int> vec;
	vec.PushBack(7);
	Vector<int> moved;
	moved = std::move(vec);
	EXPECT_EQ(moved.GetSize(), 1);
	EXPECT_EQ(moved[0], 7);
}

TEST(VectorTest, Clear)
{
	Vector<int> vec;
	vec.PushBack(1);
	vec.PushBack(2);
	vec.Clear();
	EXPECT_EQ(vec.GetSize(), 0);
}

TEST(VectorTest, IndexOutOfRange)
{
	Vector<int> vec;
	vec.PushBack(1);
	EXPECT_THROW(vec[1], std::out_of_range);
}

TEST(VectorTest, Iterators)
{
	Vector<int> vec;
	for (int i = 0; i < 5; ++i)
		vec.PushBack(i);
	int expected = 0;
	for (auto it = vec.begin(); it != vec.end(); ++it, ++expected)
		EXPECT_EQ(*it, expected);

	expected = 4;
	for (auto it = vec.rbegin(); it != vec.rend(); ++it, --expected)
		EXPECT_EQ(*it, expected);
}

TEST(VectorTest, ConstIterators)
{
	Vector<int> vec;
	for (int i = 0; i < 3; ++i)
		vec.PushBack(i);
	const Vector<int>& cref = vec;

	int expected = 0;
	for (auto it = cref.cbegin(); it != cref.cend(); ++it, ++expected)
		EXPECT_EQ(*it, expected);

	expected = 2;
	for (auto it = cref.crbegin(); it != cref.crend(); ++it, --expected)
		EXPECT_EQ(*it, expected);
}

TEST(VectorTest, DestructorCalls)
{
	Counter::constructions = 0;
	Counter::destructions = 0;
	{
		Vector<Counter> vec;
		vec.Resize(5);
	}
	EXPECT_EQ(Counter::constructions, Counter::destructions);
}