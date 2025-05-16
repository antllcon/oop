#ifndef NELSON_H
#define NELSON_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Nelson : public Person
{
public:
	Nelson(Name name, Money cash, ContactList& contact);

	Nelson(const Nelson&) = delete;
	Nelson& operator=(const Nelson&) = delete;

	void Step() override;

private:
	void StealCash();
	void PayForCigarettes();

private:
	ContactList& m_contacts;

	const Money toApu = 25;
};

#endif // NELSON_H