#include "berns.h"

Berns::Berns(Name name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
	OpenAccount();
}

void Berns::Step()
{
	PaySalary();
}

void Berns::PaySalary()
{
	auto& homer = m_contacts.GetAccountPerson(Name::Homer);
	SendMoney(homer.GetAccountId(), toEmployer);
	std::cout << "Berns pay salary for Homer " << toEmployer << std::endl;

	auto& waylon = m_contacts.GetAccountPerson(Name::Waylon);
	SendMoney(waylon.GetAccountId(), toEmployer);
	std::cout << "Berns pay salary for Waylon " << toEmployer << std::endl;
}
