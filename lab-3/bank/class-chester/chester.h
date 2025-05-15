#ifndef CHESTER_H
#define CHESTER_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Chester : public PersonWithAccount
{
public:
	Chester(const std::string& name, Money cash, Bank& bank, ContactList& contact);

	Chester(const Chester&) = delete;
	Chester& operator=(const Chester&) = delete;

	void Step() override;

private:
	void StealDeposit();
	void PayForProducts();

private:
	ContactList& m_contacts;

	const Money toApu = 100;
};

#endif // CHESTER_H