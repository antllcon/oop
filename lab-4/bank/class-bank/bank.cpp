#include "bank.h"

Bank::Bank(Money cash)
	: m_cash(cash)
{
	// AssertIsCashValid();
	if (cash < 0)
	{
		throw std::runtime_error("Negative cash is not allowed");
	}
}

// void Bank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
// {
// 	if (amount < 0)
// 	{
// 		throw std::runtime_error("You cannot transfer a negative amount of money");
// 	}

// 	if (!srcAccountId || !dstAccountId)
// 	{
// 		throw std::runtime_error("The account does not exist");
// 	}

// 	if (srcAccountId.GetMoney() < amount)
// 	{
// 		throw std::runtime_error("Not enough money");
// 	}

// 	srcAccountId.PopMoney(amount);
// 	dstAccountId.PushMoney(amount);
// };

// [[nodiscard]] Money Bank::GetCash() const { return m_cash; }

// Money GetAccountBalance(AccountId accountId) const
// {
// 	if (!accountId)
// 	{
// 		throw std::invalid_argument("The account does not exist");
// 	}

// 	return;
// }