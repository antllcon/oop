#include "lisa.h"

Lisa::Lisa(
	const std::string& name, const Money cash, Bank& bank, ContactList& contact)
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

	auto& apu = m_contacts.GetPerson("Apu");
	TransferTo(apu, toApu);
	std::cout << "Lisa buys candy from Apu" << toApu << std::endl;
}
