#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include "../class-person-with-account/person-with-account.h"
#include "../class-person/person.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

using ContactMap = std::unordered_map<std::string, std::reference_wrapper<Person>>;

class ContactList
{
public:
	ContactList() = default;
	ContactList(const ContactList&) = delete;
	ContactList& operator=(const ContactList&) = delete;

	void Add(Person& person);
	Person& GetPerson(const std::string& name) const;
	PersonWithAccount& GetAccountPerson(const std::string& name) const;
	const ContactMap& GetAllContacts() const;

private:
	void AssertIsContactExists(const std::string& name) const;
	void AssertIsContactNonExists(const std::string& name) const;

private:
	ContactMap m_registry;
};

#endif // CONTACT_LIST_H