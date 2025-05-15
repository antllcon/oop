#include "berns.h"

Berns::Berns(const std::string& name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
}

void Berns::Step()
{
	PaySalary();
}

void Berns::PaySalary()
{
	auto& homer = m_contacts.GetAccountPerson("Homer");
	SendMoney(homer.GetAccountId(), toEmployer);
	std::cout << GetName() << " pay salary for Homer " << toEmployer << std::endl;

	auto& waylon = m_contacts.GetAccountPerson("Waylon");
	SendMoney(waylon.GetAccountId(), toEmployer);
	std::cout << GetName() << " pay salary for Waylon " << toEmployer << std::endl;
}
