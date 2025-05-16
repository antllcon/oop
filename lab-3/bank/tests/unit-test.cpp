#include "../class-simulation/simulation.h"
#include "test-person.h"
#include <gtest/gtest.h>

// TEST(PersonTest, ConstructorValid)
// {
// 	TestPerson p("Name", 100);
// 	EXPECT_EQ(p.GetName(), "Name");
// 	EXPECT_EQ(p.GetMoney(), 100);
// }

// TEST(PersonTest, ConstructorInvalidName)
// {
// 	EXPECT_THROW(TestPerson("", 100), std::invalid_argument);
// }

// TEST(PersonTest, SpendCashValid)
// {
// 	TestPerson p("Name", 100);
// 	p.SpendCash(30);
// 	EXPECT_EQ(p.GetMoney(), 70);
// }

// TEST(PersonTest, SpendCashTooMuch)
// {
// 	TestPerson p("Name", 50);
// 	EXPECT_THROW(p.SpendCash(100), std::runtime_error);
// }

// TEST(PersonTest, ReceiveCashValid)
// {
// 	TestPerson p("Name", 100);
// 	p.ReceiveCash(50);
// 	EXPECT_EQ(p.GetMoney(), 150);
// }

// TEST(PersonTest, ReceiveCashOverflow)
// {
// 	TestPerson p("Name", std::numeric_limits<Money>::max() - 10);
// 	EXPECT_THROW(p.ReceiveCash(20), std::runtime_error);
// }

// TEST(PersonTest, TransferValid)
// {
// 	TestPerson p1("Name", 100);
// 	TestPerson p2("Name", 50);
// 	p1.TransferTo(p2, 30);
// 	EXPECT_EQ(p1.GetMoney(), 70);
// 	EXPECT_EQ(p2.GetMoney(), 80);
// }

// TEST(PersonTest, TransferTooMuch)
// {
// 	TestPerson p1("Ivy", 20);
// 	TestPerson p2("John", 50);
// 	EXPECT_THROW(p1.TransferTo(p2, 100), std::runtime_error);
// }
