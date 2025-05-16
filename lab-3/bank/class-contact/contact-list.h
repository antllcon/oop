#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include "../class-person-with-account/person-with-account.h"
#include "../class-person/person.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

using ContactMap = std::unordered_map<Name, std::reference_wrapper<Person>>;

class ContactList
{
public:
	ContactList() = default;
	ContactList(const ContactList&) = delete;
	ContactList& operator=(const ContactList&) = delete;

	void Add(Person& person);
	Person& GetPerson(Name name) const;
	PersonWithAccount& GetAccountPerson(Name name) const;
	const ContactMap& GetAllContacts() const;

private:
	void AssertIsContactExists(Name name) const;
	void AssertIsContactNonExists(Name name) const;

private:
	ContactMap m_registry;
};

#endif // CONTACT_LIST_H