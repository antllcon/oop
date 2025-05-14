#include "homer.h"

Homer::Homer(
	const std::string& name, const Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
}

void Homer::Step()
{
	GiveMoneyToMarge();
	PayElectricity();
	GiveMoneyToKids();
}

void Homer::GiveMoneyToMarge()
{
	// AssertIsEnoughMoney(toMarge);
	auto& marge = m_contacts.GetAccountPerson("Marge");
	SendMoney(marge.GetAccountId(), toMarge);
	std::cout << "Homer give money to Marge " << toMarge << std::endl;
}

void Homer::PayElectricity()
{
	// AssertIsEnoughMoney(toBerns);
	auto& berns = m_contacts.GetAccountPerson("Berns");
	SendMoney(berns.GetAccountId(), toBerns);
	std::cout << "Homer pay for electricity (Burns) " << toBerns << std::endl;
}

void Homer::GiveMoneyToKids()
{
	Withdraw(toLisa + toBart);

	// AssertIsEnoughMoney(toLisa);
	auto& lisa = m_contacts.GetPerson("Lisa");
	TransferTo(lisa, toLisa);
	std::cout << "Homer dive money to Lisa " << toLisa << std::endl;

	// AssertIsEnoughMoney(toBart);
	auto& bart = m_contacts.GetPerson("Bart");
	TransferTo(bart, toBart);
	std::cout << "Homer dive money to Bart " << toLisa << std::endl;
}