#include "marge.h"

Marge::Marge(Name name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.AddPersonWithAccount(*this);
	OpenAccount();
}

void Marge::Step()
{
	PayForProducts();
}

void Marge::PayForProducts()
{
	// AssertIsEnoughMoney(toApu);
	auto& apu = m_contacts.GetAccountPerson(Name::Apu);
	SendMoney(apu.GetAccountId(), toApu);
	std::cout << "Marge buys products from Apu " << toApu << std::endl;
}