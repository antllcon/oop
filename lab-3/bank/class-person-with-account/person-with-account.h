#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../class-bank/bank.h"
#include "../class-person/person.h"
#include "../types.h"
#include <optional>

class PersonWithAccount : public Person
{
public:
	explicit PersonWithAccount(Name name, Money cash, Bank& bank);
	PersonWithAccount(const PersonWithAccount&) = delete;
	PersonWithAccount& operator=(const PersonWithAccount&) = delete;

	AccountId GetDeposit() const;
	[[nodiscard]] AccountId GetAccountId() const;

	void OpenAccount();
	void CloseAccount();
	void Deposit(Money cash);
	void Withdraw(Money cash);
	void SendMoney(AccountId dstId, Money amount);

private:
	void AssertIsAccountIdExist() const;

private:
	Bank& m_bank;
	std::optional<AccountId> m_id;
};

#endif // ACCOUNT_H