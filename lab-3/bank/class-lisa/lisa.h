#ifndef LISA_H
#define LISA_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Lisa : public Person
{
public:
	Lisa(Name name, Money cash, ContactList& contact);

	Lisa(const Lisa&) = delete;
	Lisa& operator=(const Lisa&) = delete;

	void Step() override;

private:
	void PayForCandy();

private:
	ContactList& m_contacts;

	const Money toApu = 25;
};

#endif // LISA_H