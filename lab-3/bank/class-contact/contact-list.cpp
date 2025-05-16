#include "contact-list.h"

void ContactList::Add(Person& person)
{
	const auto& name = person.GetName();
	AssertIsContactNonExists(name);
	// m_registry[name] = std::ref(person);
	m_registry.emplace(name, std::ref(person));
}

Person& ContactList::GetPerson(Name name) const
{
	AssertIsContactExists(name);
	return m_registry.at(name).get();
}

const ContactMap& ContactList::GetAllContacts() const
{
	return m_registry;
}

PersonWithAccount& ContactList::GetAccountPerson(Name name) const
{
	Person& person = GetPerson(name);
	auto* personWithAccount = dynamic_cast<PersonWithAccount*>(&person);
	if (!personWithAccount)
	{
		throw std::runtime_error("Contact has no bank account");
	}
	return *personWithAccount;
}

void ContactList::AssertIsContactExists(Name name) const
{
	if (!m_registry.count(name))
	{
		throw std::runtime_error("Contact not found");
	}
}

void ContactList::AssertIsContactNonExists(Name name) const
{
	if (m_registry.count(name))
	{
		throw std::runtime_error("Contact already exists");
	}
}