#include <Date.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(DateTest, ConstructFromDayMonthYear)
{
	Date d(1, 1, 1970);
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1970);
}

TEST(DateTest, ConstructFromEpochDays)
{
	Date d(0);
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1970);
}

TEST(DateTest, DayOfWeek)
{
	Date d(1, 1, 1970);
	EXPECT_EQ(d.GetDayOfWeek(), DayOfWeek::THURSDAY);
}

TEST(DateTest, ToStringFormat)
{
	Date d(5, 12, 2023);
	EXPECT_EQ(d.ToString(), "05.12.2023");
}

TEST(DateTest, IncrementOperators)
{
	Date d(1, 1, 1970);
	++d;
	EXPECT_EQ(d.GetDay(), 2);
	d++;
	EXPECT_EQ(d.GetDay(), 3);
}

TEST(DateTest, DecrementOperators)
{
	Date d(3, 1, 1970);
	--d;
	EXPECT_EQ(d.GetDay(), 2);
	d--;
	EXPECT_EQ(d.GetDay(), 1);
}

TEST(DateTest, AdditionAndSubtraction)
{
	Date d(1, 1, 1970);
	Date d2 = d + 10;
	EXPECT_EQ(d2.GetDay(), 11);
	EXPECT_EQ((d2 - d), 10);

	Date d3 = d2 - 5;
	EXPECT_EQ(d3.GetDay(), 6);
}

TEST(DateTest, CompoundAssignment)
{
	Date d(1, 1, 1970);
	d += 30;
	EXPECT_EQ(d.GetDay(), 31);
	d -= 15;
	EXPECT_EQ(d.GetDay(), 16);
}

TEST(DateTest, ComparisonOperators)
{
	Date d1(1, 1, 1970);
	Date d2(2, 1, 1970);
	EXPECT_LT(d1, d2);
	EXPECT_GT(d2, d1);
	EXPECT_EQ(d1, Date(1, 1, 1970));
}

TEST(DateTest, MinMaxDates)
{
	EXPECT_NO_THROW(Date::Min());
	EXPECT_NO_THROW(Date::Max());
	EXPECT_NO_THROW(Date::Now());
}

TEST(DateTest, OutputOperator)
{
	Date d(5, 6, 2024);
	std::stringstream ss;
	ss << d;
	EXPECT_EQ(ss.str(), "05.06.2024");
}

TEST(DateTest, InputOperatorValid)
{
	std::stringstream ss("12.03.2020");
	Date d;
	ss >> d;
	EXPECT_FALSE(ss.fail());
	EXPECT_EQ(d.GetDay(), 12);
	EXPECT_EQ(d.GetMonth(), Month::MARCH);
	EXPECT_EQ(d.GetYear(), 2020);
}

TEST(DateTest, InputOperatorInvalid)
{
	std::stringstream ss("31-12-2020");
	Date d;
	ss >> d;
	EXPECT_TRUE(ss.fail());
}

TEST(DateTest, ValidDateThrows)
{
	EXPECT_NO_THROW(Date(29, 2, 2024));
}

TEST(DateTest, InvalidDateThrows)
{
	EXPECT_THROW(Date(30, 2, 2024), std::out_of_range);
	EXPECT_THROW(Date(1, 13, 2021), std::out_of_range);
	EXPECT_THROW(Date(1, 1, 99999), std::out_of_range);
	EXPECT_THROW(Date(Date::Max() + 1), std::out_of_range);
}

TEST(DateTest, AdditionOutOfRange)
{
	Date max = Date::Max();
	EXPECT_THROW(max + 1, std::out_of_range);
	EXPECT_THROW(max += 1, std::out_of_range);

	Date min = Date::Min();
	EXPECT_NO_THROW(min + 0);
}

TEST(DateTest, SubtractionOutOfRange)
{
	Date min = Date::Min();
	EXPECT_THROW(min - 1, std::out_of_range);
	EXPECT_THROW(min -= 1, std::out_of_range);

	Date max = Date::Max();
	EXPECT_NO_THROW(max - 0);
}

TEST(DateTest, StoreMinMax)
{
	EXPECT_NO_THROW(Date dmin = Date::Min());
	EXPECT_NO_THROW(Date dmax = Date::Max());
	EXPECT_EQ(Date::Min(), Date(1, 1, 1970));
	EXPECT_EQ(Date::Max().GetYear(), 9999);
}

TEST(DateTest, Borders)
{
	Date d(31, 12, 1970);
	++d;
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1971);
	--d;
	EXPECT_EQ(d.GetDay(), 31);
	EXPECT_EQ(d.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(d.GetYear(), 1970);
}

// Проверка корректности работы с високосным годом (29 февраля существует)
TEST(DateTest, LeapYearValidDate)
{
	Date d(29, 2, 2020);
	EXPECT_EQ(d.GetDay(), 29);
	EXPECT_EQ(d.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(d.GetYear(), 2020);
}

// Проверка перехода через конец февраля в невисокосном году
TEST(DateTest, EndOfFebruaryNonLeapYear)
{
	Date d(28, 2, 2019);
	++d;
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::MARCH);
	EXPECT_EQ(d.GetYear(), 2019);
}

// Проверка перехода через конец февраля в високосном году
TEST(DateTest, EndOfFebruaryLeapYear)
{
	Date d(28, 2, 2020);
	++d;
	EXPECT_EQ(d.GetDay(), 29);
	++d;
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::MARCH);
	EXPECT_EQ(d.GetYear(), 2020);
}

// Проверка перехода через 31 декабря (смена года)
TEST(DateTest, NewYearTransition)
{
	Date d(31, 12, 2023);
	++d;
	EXPECT_EQ(d.GetDay(), 1);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 2024);
}

// Проверка перехода при вычитании даты через 1 января (смена года назад)
TEST(DateTest, NewYearBackwardTransition)
{
	Date d(1, 1, 2024);
	--d;
	EXPECT_EQ(d.GetDay(), 31);
	EXPECT_EQ(d.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(d.GetYear(), 2023);
}

// Проверка оператора ввода на краевом допустимом значении
TEST(DateTest, InputOperatorMinDate)
{
	std::stringstream ss("01.01.1970");
	Date d;
	ss >> d;
	EXPECT_FALSE(ss.fail());
	EXPECT_EQ(d, Date::Min());
}

// Проверка оператора ввода на краевом допустимом значении максимума
TEST(DateTest, InputOperatorMaxDate)
{
	std::stringstream ss("31.12.9999");
	Date d;
	ss >> d;
	EXPECT_FALSE(ss.fail());
	EXPECT_EQ(d, Date::Max());
}

// Проверка арифметики сложения и вычитания большого числа дней (несколько лет)
TEST(DateTest, LargeDaysArithmetic)
{
	Date d(1, 1, 1970);
	Date d2 = d + 365 * 10; // 10 лет без учёта високосных
	EXPECT_EQ(d2.GetYear(), 1980);
	Date d3 = d2 - 365 * 5; // Вернуться назад на 5 лет
	EXPECT_EQ(d3.GetYear(), 1975);
}

// Проверка оператора сравнения на равенство и неравенство
TEST(DateTest, ComparisonEquality)
{
	Date d1(15, 7, 2025);
	Date d2(15, 7, 2025);
	Date d3(16, 7, 2025);
	EXPECT_EQ(d1, d2);
	EXPECT_NE(d1, d3);
	EXPECT_LT(d1, d3);
	EXPECT_GT(d3, d1);
}

// Проверка отрицательного результата вычитания двух дат
TEST(DateTest, NegativeDateDifference)
{
	Date d1(1, 1, 1980);
	Date d2(1, 1, 1990);
	EXPECT_LT(d1 - d2, 0);
	EXPECT_GT(d2 - d1, 0);
}

// Проверка оператора += и -= с нулём не изменяет дату
TEST(DateTest, CompoundAssignmentZero)
{
	Date d(15, 8, 2023);
	Date copy = d;
	d += 0;
	EXPECT_EQ(d, copy);
	d -= 0;
	EXPECT_EQ(d, copy);
}