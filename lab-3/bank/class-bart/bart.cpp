#include "bart.h"

Bart::Bart(Name name, Money cash, ContactList& contact)
	: Person(name, cash)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
}

void Bart::Step()
{
	PayForEnergyDrink();
}

void Bart::PayForEnergyDrink()
{
	// AssertIsEnoughMoney(toApu);
	auto& apu = m_contacts.GetPerson(Name::Apu);
	TransferTo(apu, toApu);
	std::cout << "Bart buys energy drink from Apu " << toApu << std::endl;
}