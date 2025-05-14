#ifndef PERSON_H
#define PERSON_H

#include "../types.h"
#include <string>

class Person
{
public:
	Person(const std::string& name, const Money cash);

	Person(Person&&) = default;
	Person& operator=(Person&&) = default;
	Person(const Person&) = delete;
	Person& operator=(const Person&) = delete;
	virtual ~Person() = default;

	[[nodiscard]] const std::string& GetName() const;
	[[nodiscard]] Money GetMoney() const;

	virtual void Step() = 0;
	void SpendCash(const Money cash);
	void ReciveCash(const Money cash);
	void TransferTo(Person& recipient, const Money cash);

protected:
	void AssertIsEnoughMoney(const Money money) const;

private:
	void AssertIsNameValid(const std::string& name) const;
	void AssertIsMoneyPositive() const;
	void AssertIsTransferMoneyValid(const Money cash) const;
	void AssertIsWalletSizeEnough(const Money cash) const;

private:
	const std::string m_name;
	Money m_cash;
};

#endif // PERSON_H