#ifndef PERSON_H
#define PERSON_H

#include "../types.h"
#include <string>

class Person
{
public:
	Person(const std::string& name, Money cash);

	Person(Person&&) = default;
	Person& operator=(Person&&) = default;
	Person(const Person&) = delete;
	Person& operator=(const Person&) = delete;
	virtual ~Person() = default;

	[[nodiscard]] const std::string& GetName() const;
	[[nodiscard]] Money GetMoney() const;

	virtual void Step() = 0;
	void SpendCash(Money cash);
	void ReceiveCash(Money cash);
	void TransferTo(Person& recipient, Money cash);

protected:
	void AssertIsEnoughMoney(Money money) const;

private:
	static void AssertIsNameValid(const std::string& name);
	void AssertIsMoneyPositive() const;
	void AssertIsTransferMoneyValid(Money cash) const;
	void AssertIsWalletSizeEnough(Money cash) const;

private:
	const std::string m_name;
	Money m_cash;
};

#endif // PERSON_H