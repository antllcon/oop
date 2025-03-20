#include "../lib.h"
#include <gtest/gtest.h>

// Правильное число аргументов и корректный формат строки
TEST(CheckArgumentsTest, ValidArguments) { EXPECT_NO_THROW(CheckArguments(2, "777")); }

// Проверка некорректного количества аргументов
TEST(CheckArgumentsTest, InvalidArgumentCount)
{
	EXPECT_THROW(CheckArguments(1, "1337"), std::runtime_error);
	EXPECT_THROW(CheckArguments(3, "228"), std::runtime_error);
}

// Проверка некорректного формата аргумента (должен быть числом)
TEST(CheckArgumentsTest, NonDigitArgument)
{
	EXPECT_THROW(CheckArguments(2, "lmao"), std::runtime_error);
}

// Генерация простых чисел для upperBound = 1 (не должно быть простых чисел)
TEST(GeneratePrimeNumbersSetTest, PrimesOne)
{
	SetPrimeNumbers expected = {};
	SetPrimeNumbers result = GeneratePrimeNumbersSet(1);
	EXPECT_EQ(result, expected);
}

// Генерация простых чисел для upperBound = 2
TEST(GeneratePrimeNumbersSetTest, PrimesTwo)
{
	SetPrimeNumbers expected = { 2 };
	SetPrimeNumbers result = GeneratePrimeNumbersSet(2);
	EXPECT_EQ(result, expected);
}

// Генерация простых чисел для upperBound = 3
TEST(GeneratePrimeNumbersSetTest, PrimesThree)
{
	SetPrimeNumbers expected = { 2, 3 };
	SetPrimeNumbers result = GeneratePrimeNumbersSet(3);
	EXPECT_EQ(result, expected);
}

// Генерация простых чисел для upperBound = 10
TEST(GeneratePrimeNumbersSetTest, PrimesTen)
{
	SetPrimeNumbers expected = { 2, 3, 5, 7 };
	SetPrimeNumbers result = GeneratePrimeNumbersSet(10);
	EXPECT_EQ(result, expected);
}

// Проверка инициализации вектора: длина и начальные значения
TEST(InitVectorTest, SizeAndInitialValues)
{
	size_t upperBound = 10;
	IsPrimeVectors vec = InitVector(upperBound);
	ASSERT_EQ(vec.size(), upperBound + 1);
	EXPECT_FALSE(vec[0]);
	EXPECT_FALSE(vec[1]);
	for (size_t i = 2; i < vec.size(); ++i)
	{
		EXPECT_TRUE(vec[i]);
	}
}

// Проверка сбора простых чисел из вектора
TEST(CollectPrimesTest, CollectFromVector)
{
	IsPrimeVectors vec(11, false);
	vec[2] = true;
	vec[3] = true;
	vec[5] = true;
	vec[7] = true;
	SetPrimeNumbers expected = { 2, 3, 5, 7 };
	SetPrimeNumbers result = CollectPrimes(vec, 10);
	EXPECT_EQ(result, expected);
}

// Проверка функции вывода: перенаправляем std::cout в строковый поток и сравниваем результат
TEST(PrintPrimeNumbersTest, OutputCapture)
{
	SetPrimeNumbers primes = { 2, 3, 5, 7 };
	std::stringstream buffer;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
	PrintPrimeNumbers(primes);
	std::cout.rdbuf(oldCoutBuffer);

	std::string expectedOutput = "2\n3\n5\n7\n";
	EXPECT_EQ(buffer.str(), expectedOutput);
}