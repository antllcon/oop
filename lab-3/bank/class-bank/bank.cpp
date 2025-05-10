#include "bank.h"
#include <random>

Bank::Bank(Money cash)
	: m_cash(cash)
// : m_accounts()
{
	// AssertIsCashValid();
	if (cash < 0)
	{
		throw std::runtime_error("Negative cash is not allowed");
	}
}

void Bank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	if (amount < 0)
	{
		throw std::runtime_error("You cannot transfer a negative amount of money");
	}

	if (!srcAccountId || !dstAccountId)
	{
		throw std::runtime_error("The account does not exist");
	}

	if (srcAccountId.GetMoney() < amount)
	{
		throw std::runtime_error("Not enough money");
	}

	srcAccountId.PopMoney(amount);
	dstAccountId.PushMoney(amount);
};

AccountId Bank::OpenAccount()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<AccountId> dist(1, 1'000'000'000);

	return dist(gen);
}

Money Bank::CloseAccount(AccountId accountId)
{
	// Что-то типо возврата денег
}

// [[nodiscard]] Money Bank::GetCash() const { return m_cash; }

// Money GetAccountBalance(AccountId accountId) const
// {
// 	if (!accountId)
// 	{
// 		throw std::invalid_argument("The account does not exist");
// 	}

// 	return;
// }