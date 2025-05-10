#include "bank-user.h"
#include <iostream>

BankUser::BankUser(Person& person)
	: m_person(person)
	, m_id(std::nullopt)
{
}

AccountId BankUser::GetAccountId() const
{
	//  Value и так выкидввает исключение, если его нет
	AssertIsAccountIdExist();
	return m_id.value();
}

void BankUser::OpenAccount(Bank& bank)
{
	m_id = bank.OpenAccount();
}

void BankUser::CloseAccount(Bank& bank)
{
	if (!m_id.has_value())
	{
		return;
	}
	auto cash = bank.CloseAccount(m_id.value());
	m_person.ReciveCash(cash);
	m_id.reset();
}

void BankUser::Deposit(Bank& bank, Money cash) const
{
	// Сохранить кэш, если выпало исключение
	m_person.SpendCash(cash);
	bank.DepositMoney(this->GetAccountId(), cash);
}

bool BankUser::TryDeposit(Bank& bank, Money cash) const
{
	return bank.TryDepositMoney(this->GetAccountId(), cash);
}

void BankUser::Withdraw(Bank& bank, Money cash) const
{
	// Сохранить кэш, если выпало исключение
	bank.WithdrawMoney(this->GetAccountId(), cash);
	m_person.ReciveCash(cash);
}

bool BankUser::TryWithdraw(Bank& bank, Money cash) const
{
	return bank.TryWithdrawMoney(this->GetAccountId(), cash);
}

void BankUser::AssertIsAccountIdExist() const
{
	if (!m_id.has_value())
	{
		throw std::runtime_error("Account ID is not set");
	}
}