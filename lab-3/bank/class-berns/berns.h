#ifndef BERNS_H
#define BERNS_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Berns : public PersonWithAccount
{
public:
	Berns(Name name, Money cash, Bank& bank, ContactList& contact);

	Berns(const Berns&) = delete;
	Berns& operator=(const Berns&) = delete;

	void Step() override;

private:
	void PaySalary();

private:
	ContactList& m_contacts;

	const int toEmployer = 400;
};

#endif // BERNS_H