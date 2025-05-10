#include "../class-bank/bank.h"
#include <gtest/gtest.h>

// Инициалзация
TEST(Bank, BankInit) { EXPECT_NO_THROW(Bank bank(30000);); }
