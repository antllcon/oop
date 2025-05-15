#include "waylon.h"
#include <random>

Waylon::Waylon(const std::string& name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
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
	std::cout << GetName() << " opens a new paranoid account" << std::endl;
}

void Waylon::PayForProducts()
{
	// AssertIsEnoughMoney(toApu);
	auto& apu = m_contacts.GetAccountPerson("Apu");
	SendMoney(apu.GetAccountId(), toApu);
	std::cout << GetName() << " buys products from Apu " << toApu << std::endl;
}