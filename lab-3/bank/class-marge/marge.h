#ifndef MARGE_H
#define MARGE_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Marge : public PersonWithAccount
{
public:
	Marge(Name name, Money cash, Bank& bank, ContactList& contact);

	Marge(const Marge&) = delete;
	Marge& operator=(const Marge&) = delete;

	void Step() override;

private:
	void PayForProducts();

private:
	ContactList& m_contacts;

	const Money toApu = 100;
};

#endif // MARGE_H