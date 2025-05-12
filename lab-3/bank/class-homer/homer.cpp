#include "homer.h"

Homer::Homer(
	const std::string& name, const Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contact(contact)
{
}

void Homer::Step()
{
	try
	{
		GiveMoneyToMarge();
		PayElectricity();
		GiveMoneyToKids();
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		std::cout << "Homer skip this step" << std::endl;
	}
}

void Homer::GiveMoneyToMarge()
{
	AssertIsEnoughMoney(toMarge);
	auto& marge = m_contact.GetAccountPerson("Marge");
	SendMoney(marge.GetAccountId(), toMarge);
}

void Homer::PayElectricity()
{
	AssertIsEnoughMoney(toBerns);
	auto& berns = m_contact.GetAccountPerson("Berns");
	SendMoney(berns.GetAccountId(), toBerns);
}

void Homer::GiveMoneyToKids()
{
	AssertIsEnoughMoney(toLisa);
	auto& lisa = m_contact.GetPerson("Lisa");
	TransferTo(lisa, toLisa);

	AssertIsEnoughMoney(toBart);
	auto& bart = m_contact.GetPerson("Bart");
	TransferTo(bart, toBart);
}

void Homer::AssertIsEnoughMoney(const Money money) const
{
	if (GetMoney() < money)
	{
		throw std::runtime_error("Is there enough money for the transaction");
	}
}

// Стоит ли делать обраоботку ошибок, если мы не сможем проверить работу класса
// bank?
