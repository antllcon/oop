#include "marge.h"

Marge::Marge(
	const std::string& name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
}

void Marge::Step()
{
	PayForProducts();
}

void Marge::PayForProducts()
{
	// AssertIsEnoughMoney(toApu);
	auto& apu = m_contacts.GetAccountPerson("Apu");
	SendMoney(apu.GetAccountId(), toApu);
	std::cout << "Marge buys products from Apu" << toApu << std::endl;
}