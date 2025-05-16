#include "lisa.h"

Lisa::Lisa(Name name, Money cash, ContactList& contact)
	: Person(name, cash)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
}

void Lisa::Step()
{
	PayForCandy();
}

void Lisa::PayForCandy()
{
	// AssertIsEnoughMoney(toApu);

	auto& apu = m_contacts.GetPerson(Name::Apu);
	TransferTo(apu, toApu);
	std::cout << "Lisa buys candy from Apu " << toApu << std::endl;
}
