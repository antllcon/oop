#include "berns.h"

Berns::Berns(
	const std::string& name, const Money cash, Bank& bank, ContactList& contact)
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
	std::cout << "Berns pay salary for employers" << toEmployer << std::endl;
}
