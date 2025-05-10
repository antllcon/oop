#include "../types.h"
#include <string>

// TODO: сделать класс обработки исклчений

class Person
{
public:
	Person(const std::string& name, const Money cash);

	Person(Person&&) = default;
	Person& operator=(Person&&) = default;
	Person(const Person&) = delete;
	Person& operator=(const Person&) = delete;

	[[nodiscard]] const std::string& GetName() const;
	[[nodiscard]] Money GetMoney() const;

	void SpendCash(const Money cash);
	void ReciveCash(const Money cash);
	void TransferTo(Person& recipient, const Money cash);

private:
	void AssertIsNameNoEmpty() const;
	void AssertIsMoneyPositive() const;
	void AssertIsTransferMoneyValid(const Money cash) const;
	void AssertIsWalletSizeEnough(const Money cash) const;

private:
	std::string m_name;
	Money m_cash;
};