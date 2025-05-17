#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-simulation/simulation.h"
#include "test-person-with-account.h"
#include "test-person.h"
#include <gtest/gtest.h>

// Тесты для класса Person
TEST(PersonTest, Init)
{
	TestPerson p(Name::Homer, 100);
	EXPECT_EQ(p.GetName(), Name::Homer);
	EXPECT_EQ(p.GetMoney(), 100);
}

TEST(PersonTest, ReceiveCash)
{
	TestPerson p(Name::Bart, 50);
	p.ReceiveCash(30);
	EXPECT_EQ(p.GetMoney(), 80);
}

TEST(PersonTest, SpendCash)
{
	TestPerson p(Name::Lisa, 100);
	p.SpendCash(40);
	EXPECT_EQ(p.GetMoney(), 60);
}

TEST(PersonTest, SpendCashThrowsIfNotEnough)
{
	TestPerson p(Name::Marge, 10);
	EXPECT_THROW(p.SpendCash(20), std::runtime_error);
}

TEST(PersonTest, TransferTo)
{
	TestPerson p1(Name::Apu, 100);
	TestPerson p2(Name::Nelson, 50);
	p1.TransferTo(p2, 30);
	EXPECT_EQ(p1.GetMoney(), 70);
	EXPECT_EQ(p2.GetMoney(), 80);
}

TEST(PersonTest, TransferToThrowsIfNotEnough)
{
	TestPerson p1(Name::Berns, 10);
	TestPerson p2(Name::Waylon, 10);
	EXPECT_THROW(p1.TransferTo(p2, 20), std::runtime_error);
}

// Тесты для класса PersonWithAccount
TEST(PersonWithAccountTest, OpenAndCloseAccount)
{
	Bank bank(1000);
	TestPersonWithAccount p(Name::Homer, 100, bank);

	p.OpenAccount();
	EXPECT_NO_THROW(AccountId id = p.GetAccountId());
	EXPECT_EQ(bank.GetAccountBalance(p.GetAccountId()), 0);

	p.Deposit(50);
	EXPECT_EQ(bank.GetAccountBalance(p.GetAccountId()), 50);
	EXPECT_EQ(p.GetMoney(), 50);

	p.CloseAccount();
	EXPECT_THROW(AccountId id = p.GetAccountId(), std::runtime_error);
	EXPECT_EQ(p.GetMoney(), 100); // Деньги вернулись на руки
}

TEST(PersonWithAccountTest, DepositAndWithdraw)
{
	Bank bank(1000);
	TestPersonWithAccount p(Name::Marge, 200, bank);

	p.OpenAccount();
	p.Deposit(100);
	EXPECT_EQ(bank.GetAccountBalance(p.GetAccountId()), 100);
	EXPECT_EQ(p.GetMoney(), 100);

	p.Withdraw(50);
	EXPECT_EQ(bank.GetAccountBalance(p.GetAccountId()), 50);
	EXPECT_EQ(p.GetMoney(), 150);
}

TEST(PersonWithAccountTest, WithdrawThrowsIfNotEnough)
{
	Bank bank(1000);
	TestPersonWithAccount p(Name::Bart, 100, bank);

	p.OpenAccount();
	p.Deposit(100);
	EXPECT_THROW(p.Withdraw(200), BankOperationError);
}

TEST(PersonWithAccountTest, SendMoney)
{
	Bank bank(1000);
	TestPersonWithAccount p1(Name::Apu, 300, bank);
	TestPersonWithAccount p2(Name::Berns, 100, bank);

	p1.OpenAccount();
	p2.OpenAccount();

	p1.Deposit(200);
	p2.Deposit(100);

	p1.SendMoney(p2.GetAccountId(), 150);

	EXPECT_EQ(bank.GetAccountBalance(p1.GetAccountId()), 50);
	EXPECT_EQ(bank.GetAccountBalance(p2.GetAccountId()), 250);
}

TEST(PersonWithAccountTest, DepositThrowsIfNoAccount)
{
	Bank bank(1000);
	TestPersonWithAccount p(Name::Nelson, 100, bank);

	EXPECT_THROW(p.Deposit(50), std::runtime_error);
}

TEST(PersonWithAccountTest, WithdrawThrowsIfNoAccount)
{
	Bank bank(1000);
	TestPersonWithAccount p(Name::Waylon, 100, bank);

	EXPECT_THROW(p.Withdraw(50), std::runtime_error);
}

TEST(PersonWithAccountTest, SendMoneyThrowsIfNoAccount)
{
	Bank bank(1000);
	TestPersonWithAccount p1(Name::Lisa, 100, bank);
	TestPersonWithAccount p2(Name::Chester, 100, bank);

	p2.OpenAccount();
	EXPECT_THROW(p1.SendMoney(p2.GetAccountId(), 10), std::runtime_error);
}

TEST(ContactListTest, AddAndGetPerson)
{
	ContactList contacts;
	TestPerson p(Name::Lisa, 100);
	contacts.AddPerson(p);

	Person& ref = contacts.GetPerson(Name::Lisa);
	EXPECT_EQ(&ref, &p);
	EXPECT_EQ(ref.GetName(), Name::Lisa);
}

TEST(ContactListTest, AddAndGetAccountPerson)
{
	Bank bank(1000);
	ContactList contacts;
	TestPersonWithAccount p(Name::Marge, 200, bank);
	p.OpenAccount();
	contacts.AddPersonWithAccount(p);

	PersonWithAccount& ref = contacts.GetAccountPerson(Name::Marge);
	EXPECT_EQ(&ref, &p);
	EXPECT_EQ(ref.GetAccountId(), p.GetAccountId());
}

TEST(ContactListTest, ThrowsIfContactNotFound)
{
	ContactList contacts;
	EXPECT_THROW(contacts.GetPerson(Name::Bart), std::runtime_error);
	EXPECT_THROW(contacts.GetAccountPerson(Name::Bart), std::runtime_error);
}

TEST(ContactListTest, ThrowsIfContactAlreadyExists)
{
	ContactList contacts;
	TestPerson p(Name::Lisa, 50);
	contacts.AddPerson(p);
	EXPECT_THROW(contacts.AddPerson(p), std::runtime_error);
}

TEST(ContactListTest, ThrowsIfContactAlreadyExistsNew)
{
	Bank bank(2000);
	ContactList contacts;
	TestPersonWithAccount p(Name::Homer, 50, bank);
	contacts.AddPersonWithAccount(p);
	EXPECT_THROW(contacts.AddPersonWithAccount(p), std::runtime_error);
}

TEST(ContactListTest, ThrowsIfNoBankAccount)
{
	ContactList contacts;
	TestPerson p(Name::Nelson, 10);
	contacts.AddPerson(p);
	EXPECT_THROW(contacts.GetAccountPerson(Name::Nelson), std::out_of_range);
}

TEST(ContactListTest, GetAllContacts)
{
	ContactList contacts;
	TestPerson p1(Name::Apu, 100);
	Bank bank(1000);
	TestPersonWithAccount p2(Name::Berns, 200, bank);

	contacts.AddPerson(p1);
	contacts.AddPersonWithAccount(p2);

	const auto& all = contacts.GetAllContacts();
	EXPECT_EQ(all.person.size(), 1);
	EXPECT_EQ(all.personWithAccount.size(), 1);
	EXPECT_TRUE(all.person.count(Name::Apu));
	EXPECT_TRUE(all.personWithAccount.count(Name::Berns));
}

TEST(BankTest, InitAndGetCash)
{
	Bank bank(1000);
	EXPECT_EQ(bank.GetCash(), 1000);
	EXPECT_EQ(bank.GetDeposits(), 0);
}

TEST(BankTest, OpenAndCloseAccount)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	EXPECT_EQ(bank.GetAccountBalance(id), 0);

	// Пополнили счет, потом закрыли
	bank.DepositMoney(id, 500);
	EXPECT_EQ(bank.GetAccountBalance(id), 500);
	EXPECT_EQ(bank.GetCash(), 500);

	Money returned = bank.CloseAccount(id);
	EXPECT_EQ(returned, 500);
	EXPECT_EQ(bank.GetCash(), 1000);
}

TEST(BankTest, DepositMoney)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 300);
	EXPECT_EQ(bank.GetAccountBalance(id), 300);
	EXPECT_EQ(bank.GetCash(), 700);
}

TEST(BankTest, WithdrawMoney)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 400);
	bank.WithdrawMoney(id, 150);
	EXPECT_EQ(bank.GetAccountBalance(id), 250);
	EXPECT_EQ(bank.GetCash(), 750);
}

TEST(BankTest, SendMoney)
{
	Bank bank(1000);
	AccountId id1 = bank.OpenAccount();
	AccountId id2 = bank.OpenAccount();
	bank.DepositMoney(id1, 500);
	bank.SendMoney(id1, id2, 200);
	EXPECT_EQ(bank.GetAccountBalance(id1), 300);
	EXPECT_EQ(bank.GetAccountBalance(id2), 200);
}

TEST(BankTest, TryDepositMoney)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	EXPECT_TRUE(bank.TryDepositMoney(id, 500));
	EXPECT_EQ(bank.GetAccountBalance(id), 500);
	EXPECT_EQ(bank.GetCash(), 500);

	// Попытка внести больше, чем есть в банке
	EXPECT_FALSE(bank.TryDepositMoney(id, 600));
}

TEST(BankTest, TryWithdrawMoney)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 300);
	EXPECT_TRUE(bank.TryWithdrawMoney(id, 200));
	EXPECT_EQ(bank.GetAccountBalance(id), 100);
	EXPECT_EQ(bank.GetCash(), 900);

	// Попытка снять больше, чем есть на счете
	EXPECT_FALSE(bank.TryWithdrawMoney(id, 200));
}

TEST(BankTest, TrySendMoney)
{
	Bank bank(1000);
	AccountId id1 = bank.OpenAccount();
	AccountId id2 = bank.OpenAccount();
	bank.DepositMoney(id1, 400);

	EXPECT_TRUE(bank.TrySendMoney(id1, id2, 200));
	EXPECT_EQ(bank.GetAccountBalance(id1), 200);
	EXPECT_EQ(bank.GetAccountBalance(id2), 200);

	// Попытка перевести больше, чем есть
	EXPECT_FALSE(bank.TrySendMoney(id1, id2, 300));
}

TEST(BankTest, DepositMoneyThrowsIfNegative)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	EXPECT_THROW(bank.DepositMoney(id, -10), std::out_of_range);
}

TEST(BankTest, WithdrawMoneyThrowsIfNegative)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 100);
	EXPECT_THROW(bank.WithdrawMoney(id, -10), std::out_of_range);
}

TEST(BankTest, WithdrawMoneyThrowsIfNotEnough)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 50);
	EXPECT_THROW(bank.WithdrawMoney(id, 100), BankOperationError);
}

TEST(BankTest, DepositMoneyThrowsIfNotEnoughCash)
{
	Bank bank(100);
	AccountId id = bank.OpenAccount();
	EXPECT_THROW(bank.DepositMoney(id, 200), BankOperationError);
}

TEST(BankTest, SendMoneyThrowsIfNotEnough)
{
	Bank bank(1000);
	AccountId id1 = bank.OpenAccount();
	AccountId id2 = bank.OpenAccount();
	bank.DepositMoney(id1, 100);
	EXPECT_THROW(bank.SendMoney(id1, id2, 200), BankOperationError);
}

TEST(BankTest, AccountExistenceChecks)
{
	Bank bank(1000);
	EXPECT_THROW(Money money = bank.GetAccountBalance(999), BankOperationError);
	EXPECT_THROW(bank.DepositMoney(999, 10), BankOperationError);
	EXPECT_THROW(bank.WithdrawMoney(999, 10), BankOperationError);
	EXPECT_THROW(bank.SendMoney(999, 0, 10), BankOperationError);
	EXPECT_THROW(bank.SendMoney(0, 999, 10), BankOperationError);
}

// Тесты для simulation
// TEST(SimulationTest, BasicSimulation)
// {
// 	Simulation simulation(90000, 1000);
// 	EXPECT_NO_THROW(simulation.RunSimulation());
// }