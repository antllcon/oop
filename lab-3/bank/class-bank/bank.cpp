#include "bank.h"

Bank::Bank(Money cash)
	: m_cash(cash)
{
	AssertIsNonNegativeMoney(cash);
}

Money Bank::GetCash() const
{
	return m_cash;
}

Money Bank::GetDeposits() const
{
	Money deposits = 0;
	for (const auto& [id, deposit] : m_accounts)
	{
		deposits += deposit;
	}
	return deposits;
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

Money Bank::CloseAccount(AccountId id)
{
	auto balance = GetAccountBalance(id);
	m_accounts.erase(m_accounts.find(id));
	m_cash += balance;
	return balance;
}

void Bank::DepositMoney(AccountId id, Money amount)
{
	AssertIsNonNegativeMoney(amount);
	AssertIsAccountExist(id);
	AssertIsAmountIsMoreCash(amount);

	m_accounts[id] += amount;
	m_cash -= amount;
}

bool Bank::TryDepositMoney(AccountId id, Money amount)
{
	if (amount < 0)
	{
		return false;
	}
	if (m_cash < amount)
	{
		return false;
	}
	if (m_accounts.find(id) == m_accounts.end())
	{
		return false;
	}
	m_accounts[id] += amount;
	m_cash -= amount;
	return true;
}

void Bank::WithdrawMoney(AccountId id, Money amount)
{
	AssertIsNonNegativeMoney(amount);
	AssertIsAccountExist(id);
	AssertIsAmountValid(id, amount);
	AssertIsAmountIsMoreCash(amount);

	m_accounts[id] -= amount;
	m_cash += amount;
}

bool Bank::TryWithdrawMoney(AccountId id, Money amount)
{
	if (amount < 0)
	{
		return false;
	}
	if (m_accounts.find(id) == m_accounts.end())
	{
		return false;
	}
	if (GetAccountBalance(id) < amount)
	{
		return false;
	}
	m_accounts[id] -= amount;
	m_cash += amount;
	return true;
}

void Bank::SendMoney(AccountId srcId, AccountId dstId, Money amount)
{
	AssertIsNonNegativeMoney(amount);
	AssertIsAccountExist(srcId);
	AssertIsAccountExist(dstId);
	AssertIsAmountValid(srcId, amount);

	m_accounts[srcId] -= amount;
	m_accounts[dstId] += amount;
}

bool Bank::TrySendMoney(AccountId srcId, AccountId dstId, Money amount)
{
	if (amount < 0)
	{
		return false;
	}
	if (GetAccountBalance(srcId) < amount)
	{
		return false;
	}
	if (m_accounts.find(srcId) == m_accounts.end())
	{
		return false;
	}
	if (m_accounts.find(dstId) == m_accounts.end())
	{
		return false;
	}
	if (m_accounts[srcId] < amount)
	{
		return false;
	}
	m_accounts[srcId] -= amount;
	m_accounts[dstId] += amount;
	return true;
}

void Bank::AssertIsAccountExist(AccountId id) const
{
	if (m_accounts.find(id) == m_accounts.end())
	{
		throw BankOperationError("Account does not exist");
	}
}

void Bank::AssertIsNonNegativeMoney(Money money)
{
	if (money < 0)
	{
		throw std::out_of_range("Negative amount is not allowed");
	}
}

void Bank::AssertIsAmountValid(AccountId id, Money money) const
{
	if (m_accounts.at(id) < money)
	{
		throw BankOperationError("Account does not include this amount");
	}
}

void Bank::AssertIsAmountIsMoreCash(Money money) const
{
	if (m_cash < money)
	{
		throw BankOperationError("The amount is more than cash");
	}
}