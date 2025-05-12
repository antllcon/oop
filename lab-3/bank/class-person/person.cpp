#include "person.h"
#include <iostream>
#include <limits>

Person::Person(const std::string& name, const Money cash)
	: m_name(name)
	, m_cash(0)
{
	AssertIsNameValid(name);
	AssertIsWalletSizeEnough(cash);
	m_cash = cash;
	AssertIsMoneyPositive();
}

const std::string& Person::GetName() const
{
	return m_name;
}

Money Person::GetMoney() const
{
	return m_cash;
}

void Person::SpendCash(const Money cash)
{
	AssertIsMoneyPositive();
	AssertIsTransferMoneyValid(cash);
	m_cash = m_cash - cash;
}

void Person::ReciveCash(const Money cash)
{
	AssertIsWalletSizeEnough(cash);
	m_cash = m_cash + cash;
}

void Person::TransferTo(Person& recipient, const Money cash)
{
	SpendCash(cash);
	recipient.ReciveCash(cash);
}

void Person::AssertIsNameValid(const std::string& name) const
{
	if (name.empty())
	{
		throw std::invalid_argument("The name must be not empty");
	}
}

void Person::AssertIsMoneyPositive() const
{
	if (m_cash < 0)
	{
		throw std::invalid_argument("The money must be positive");
	}
}

void Person::AssertIsTransferMoneyValid(const Money cash) const
{
	if (cash > m_cash)
	{
		throw std::runtime_error("You can only transfer your amount of money");
	}
}

void Person::AssertIsWalletSizeEnough(const Money cash) const
{
	if (m_cash > std::numeric_limits<Money>::max() - cash)
	{
		throw std::runtime_error("There is no place for money");
	}
}