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