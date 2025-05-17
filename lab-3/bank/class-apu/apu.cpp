#include "apu.h"

Apu::Apu(Name name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.AddPersonWithAccount(*this);
	OpenAccount();
}

void Apu::Step()
{
	if (GetMoney() > 0)
	{
		DepositCash();
	}
	PayElectricity();
}

void Apu::PayElectricity()
{
	//	 AssertIsEnoughMoney(toBerns);
	auto& berns = m_contacts.GetAccountPerson(Name::Berns);
	SendMoney(berns.GetAccountId(), toBerns);
	std::cout << "Apu pay for electricity (Burns) " << toBerns << std::endl;
}

void Apu::DepositCash()
{
	// AssertIsEnoughMoney(toLisa);
	Deposit(GetMoney());
	std::cout << "Apu deposit money to bank account " << GetMoney() << std::endl;
}