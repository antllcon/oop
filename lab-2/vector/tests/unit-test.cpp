#include "../numbers.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(ReadNumbersTest, ReadsCorrectlyNormal)
{
	std::vector<double> numbers;
	std::istringstream input("1.0 2.0 3.0");
	std::cin.rdbuf(input.rdbuf());

	EXPECT_NO_THROW(ReadNumbers(numbers));
	ASSERT_EQ(numbers.size(), 3);
	EXPECT_EQ(numbers[0], 1.0);
	EXPECT_EQ(numbers[1], 2.0);
	EXPECT_EQ(numbers[2], 3.0);
}

TEST(ReadNumbersTest, ReadsInvalid)
{
	std::vector<double> numbers;
	std::istringstream input("1.0 wrong 3.0");
	std::cin.rdbuf(input.rdbuf());

	EXPECT_THROW(ReadNumbers(numbers), std::runtime_error);
}

TEST(ProcessNumbersTest, HandlesNormalVector)
{
	std::vector<double> numbers = { 5.0, 3.0, 1.0 };
	std::vector<double> expected = { 14.0, 12.0, 10.0 };
	ProcessNumbers(numbers);

	ASSERT_EQ(numbers.size(), 3);
	EXPECT_EQ(numbers, expected);
}

TEST(ProcessNumbersTest, HandlesSmallVector)
{
	std::vector<double> numbers = { 1.0, 2.0 };
	std::vector<double> expected = { 4.0, 5.0 };
	ProcessNumbers(numbers);

	ASSERT_EQ(numbers.size(), 2);
	EXPECT_EQ(numbers, expected);
}

TEST(ProcessNumbersTest, HandlesEmptyVector)
{
	std::vector<double> numbers;
	ProcessNumbers(numbers);

	ASSERT_EQ(numbers.size(), 0);
	EXPECT_TRUE(numbers.empty());
}

TEST(PrintSortedNumbersTest, PrintsCorrectly)
{
	std::vector<double> numbers = { 3.0, 1.0, 2.0 };
	std::ostringstream output;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	PrintSortedNumbers(numbers);
	std::cout.rdbuf(oldCoutBuffer);

	EXPECT_EQ(output.str(), "1.000 2.000 3.000\n");
}

TEST(PrintSortedNumbersTest, HandlesEmptyVector)
{
	std::vector<double> numbers;
	std::ostringstream output;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	PrintSortedNumbers(numbers);
	std::cout.rdbuf(oldCoutBuffer);

	EXPECT_EQ(output.str(), "\n");
}