#ifndef BART_H
#define BART_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Bart : public Person
{
public:
	Bart(Name name, Money cash, ContactList& contact);

	Bart(const Bart&) = delete;
	Bart& operator=(const Bart&) = delete;

	void Step() override;

private:
	void PayForEnergyDrink();

private:
	ContactList& m_contacts;

	const Money toApu = 25;
};

#endif // BART_H