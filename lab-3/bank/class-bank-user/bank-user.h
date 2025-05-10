#ifndef BANK_USER_H
#define BANK_USER_H
#include "../class-bank/bank.h"
#include "../class-person/person.h"
#include "../types.h"
#include <optional>

class BankUser
{
public:
	explicit BankUser(Person& person);

	BankUser(const BankUser&) = delete;
	BankUser& operator=(const BankUser&) = delete;

	[[nodiscard]] AccountId GetAccountId() const;

	void OpenAccount(Bank& bank);
	void CloseAccount(Bank& bank);
	void Deposit(Bank& bank, Money cash) const;
	void Withdraw(Bank& bank, Money cash) const;

	bool TryDeposit(Bank& bank, Money cash) const;
	bool TryWithdraw(Bank& bank, Money cash) const;

private:
	void AssertIsAccountIdExist() const;

private:
	Person& m_person;
	std::optional<AccountId> m_id;
};

#endif // BANK_USER_H