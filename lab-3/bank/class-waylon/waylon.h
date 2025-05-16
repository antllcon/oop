#ifndef WAYLON_H
#define WAYLON_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Waylon : public PersonWithAccount
{
public:
	Waylon(Name name, Money cash, Bank& bank, ContactList& contact);

	Waylon(const Waylon&) = delete;
	Waylon& operator=(const Waylon&) = delete;

	void Step() override;

private:
	void Paranoia();
	void PayForProducts();

private:
	ContactList& m_contacts;

	const Money toApu = 100;
};

#endif // WAYLON_H