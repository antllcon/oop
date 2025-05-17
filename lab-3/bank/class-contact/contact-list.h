#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include "../class-person-with-account/person-with-account.h"
#include "../class-person/person.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

struct ContactMaps
{
	std::unordered_map<Name, std::reference_wrapper<Person>> person;
	std::unordered_map<Name, std::reference_wrapper<PersonWithAccount>>
		personWithAccount;
};

class ContactList
{
public:
	ContactList() = default;
	ContactList(const ContactList&) = delete;
	ContactList& operator=(const ContactList&) = delete;

	void AddPerson(Person& person);
	void AddPersonWithAccount(PersonWithAccount& person);
	Person& GetPerson(Name name) const;
	PersonWithAccount& GetAccountPerson(Name name) const;
	const ContactMaps& GetAllContacts() const;

private:
	void AssertIsContactExists(Name name) const;
	void AssertIsContactNonExists(Name name) const;

private:
	ContactMaps m_registry;
};

#endif // CONTACT_LIST_H