#ifndef APU_H
#define APU_H

#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person-with-account/person-with-account.h"
#include "../types.h"
#include <set>

class Apu : public PersonWithAccount
{
public:
	Apu(const std::string& name, const Money cash, Bank& bank, ContactList& contact);

	Apu(const Apu&) = delete;
	Apu& operator=(const Apu&) = delete;

	void Step();

private:
	void DepositCash();
	void PayElectricity();

private:
	ContactList& m_contacts;
	const int toBerns = 200;
};

#endif // APU_H