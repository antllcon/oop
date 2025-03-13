#include "../numbers.h"
#include <gtest/gtest.h>
#include <sstream>

// Тесты для ReadNumbers
TEST(ReadNumbersTest, ReadsNumbersCorrectly)
{
	std::vector<double> numbers;
	std::istringstream input("1.5 2.3 3.7 4.1");

	std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
	ReadNumbers(numbers);
	std::cin.rdbuf(oldCin);

	std::vector<double> expected = { 1.5, 2.3, 3.7, 4.1 };
	EXPECT_EQ(numbers, expected);
}

TEST(ReadNumbersTest, ThrowsExceptionOnInvalidInput)
{
	std::vector<double> numbers;
	std::istringstream input("1.5 abc 3.7");

	std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
	EXPECT_THROW(ReadNumbers(numbers), std::runtime_error);
	std::cin.rdbuf(oldCin);
}

// Тесты для ProcessNumbers
TEST(ProcessNumbersTest, HandlesEmptyVector)
{
	std::vector<double> numbers;
	ProcessNumbers(numbers);
	EXPECT_TRUE(numbers.empty());
}

TEST(ProcessNumbersTest, ProcessesNumbersCorrectly)
{
	std::vector<double> numbers = { 5.0, 3.0, 1.0, 4.0, 2.0 };
	ProcessNumbers(numbers);

	std::vector<double> expected = { 11.0, 9.0, 7.0, 10.0, 8.0 };
	EXPECT_EQ(numbers, expected);
}

TEST(ProcessNumbersTest, HandlesSmallVector)
{
	std::vector<double> numbers = { 1.0, 2.0 };
	ProcessNumbers(numbers);

	std::vector<double> expected = { 4.0, 5.0 };
	EXPECT_EQ(numbers, expected);
}

// Тесты для PrintSortedNumbers
TEST(PrintSortedNumbersTest, PrintsSortedNumbersCorrectly)
{
	std::vector<double> numbers = { 5.0, 3.0, 1.0, 4.0, 2.0 };
	std::ostringstream output;

	std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
	PrintSortedNumbers(numbers);
	std::cout.rdbuf(oldCout);

	std::string expected = "1.000 2.000 3.000 4.000 5.000\n";
	EXPECT_EQ(output.str(), expected);
}