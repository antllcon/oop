#ifndef HOMER_H
#define HOMER_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Homer : public PersonWithAccount
{
public:
	Homer(
		const std::string& name, Money cash, Bank& bank, ContactList& contact);

	Homer(const Homer&) = delete;
	Homer& operator=(const Homer&) = delete;

	void Step() override;

private:
	void GiveMoneyToMarge();
	void PayElectricity();
	void GiveMoneyToKids();

private:
	ContactList& m_contacts;

	const Money toMarge = 100;
	const Money toBerns = 200;
	const Money toBart = 50;
	const Money toLisa = 50;
};

#endif // HOMER_H