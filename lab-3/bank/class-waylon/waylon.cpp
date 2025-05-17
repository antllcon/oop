#include "waylon.h"
#include <random>

Waylon::Waylon(Name name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.AddPersonWithAccount(*this);
	OpenAccount();
}

void Waylon::Step()
{
	if (RandomChance(1, 3))
	{
		Paranoia();
	}
	PayForProducts();
}

void Waylon::Paranoia()
{
	CloseAccount();
	OpenAccount();
	Deposit(GetMoney());
	std::cout << "Waylon opens a new paranoid account" << std::endl;
}

void Waylon::PayForProducts()
{
	// AssertIsEnoughMoney(toApu);
	auto& apu = m_contacts.GetAccountPerson(Name::Apu);
	SendMoney(apu.GetAccountId(), toApu);
	std::cout << "Waylon buys products from Apu " << toApu << std::endl;
}