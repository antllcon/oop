#include "bank.h"

Bank::Bank(Money cash)
	: m_cash(cash)
{
	AssertIsNonNegaiveMoney(cash);
}

Money Bank::GetCash() const
{
	return m_cash;
}

Money Bank::GetAccountBalance(AccountId id) const
{
	AssertIsAccountExist(id);
	return m_accounts.at(id);
}

AccountId Bank::OpenAccount()
{
	auto id = m_nextAccountId++;
	m_accounts[id] = 0;
	return id;
}

Money Bank::CloseAccount(const AccountId id)
{
	auto balance = GetAccountBalance(id);
	m_accounts.erase(m_accounts.find(id));
	return balance;
}

void Bank::DepositMoney(AccountId id, Money amount)
{
	if (!TryDepositMoney(id, amount))
	{
		throw BankOperationError("Deposit operation failed");
	}

	m_accounts[id] += amount;
	m_cash -= amount;
}

bool Bank::TryDepositMoney(AccountId id, Money amount)
{
	AssertIsNonNegaiveMoney(amount);

	if (m_cash < amount)
	{
		return false;
	}

	AssertIsAccountExist(id);
	return true;
}

void Bank::WithdrawMoney(AccountId id, Money amount)
{
	if (!TryWithdrawMoney(id, amount))
	{
		throw BankOperationError("Withdraw operation failed");
	}

	m_accounts[id] -= amount;
	m_cash += amount;
}

bool Bank::TryWithdrawMoney(AccountId id, Money amount)
{
	AssertIsNonNegaiveMoney(amount);
	if (GetAccountBalance(id) < amount)
	{
		return false;
	}
	return true;
}

void Bank::SendMoney(AccountId srcId, AccountId dstId, Money amount)
{
	if (!TrySendMoney(srcId, dstId, amount))
	{
		throw BankOperationError("Couldn't transfer money");
	}

	m_accounts[srcId] -= amount;
	m_accounts[dstId] += amount;
}

bool Bank::TrySendMoney(AccountId srcId, AccountId dstId, Money amount)
{
	AssertIsNonNegaiveMoney(amount);
	AssertIsAccountExist(srcId);
	AssertIsAccountExist(dstId);
	if (GetAccountBalance(srcId) < amount)
	{
		return false;
	}
	return true;
}

void Bank::AssertIsAccountExist(AccountId id) const
{
	if (m_accounts.find(id) == m_accounts.end())
	{
		return throw BankOperationError("Account does not exist");
	}
}

void Bank::AssertIsNonNegaiveMoney(Money money) const
{
	if (money < 0)
	{
		throw std::out_of_range("Negative amount is not allowed");
	}
}