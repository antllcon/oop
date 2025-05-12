#include "contact-list.h"

void ContactList::Add(Person& person)
{
	const auto& name = person.GetName();
	AssertIsContactNonExists(name);
	m_registry[name] = std::ref(person);
	;
}

Person& ContactList::GetPerson(const std::string& name) const
{
	AssertIsContactExists(name);
	return m_registry.at(name).get();
}

PersonWithAccount& ContactList::GetAccountPerson(const std::string& name) const
{
	Person& person = GetPerson(name);
	auto* personWithAccount = dynamic_cast<PersonWithAccount*>(&person);
	if (!personWithAccount)
	{
		throw std::runtime_error("Contact " + name + " has no bank account");
	}
	return *personWithAccount;
}

void ContactList::AssertIsContactExists(const std::string& name) const
{
	if (!m_registry.count(name))
	{
		throw std::runtime_error("Contact not found: " + name);
	}
}

void ContactList::AssertIsContactNonExists(const std::string& name) const
{
	if (m_registry.count(name))
	{
		throw std::runtime_error("Contact already exists: " + name);
	}
}