#include "chester.h"
#include <random>

Chester::Chester(Name name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.AddPersonWithAccount(*this);
	OpenAccount();
}

void Chester::Step()
{
	if (RandomChance(1, 3))
	{
		StealDeposit();
	}
	PayForProducts();
}

void Chester::StealDeposit()
{
	auto& homer = m_contacts.GetAccountPerson(Name::Homer);
	Money available = homer.GetDeposit();

	if (available <= 0)
	{
		std::cout << "Chester tried to hack Homer, but his account is empty."
				  << std::endl;
		return;
	}

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<Money> dist(1, available);
	Money stolen = dist(gen);

	homer.SendMoney(this->GetAccountId(), stolen);
	std::cout << "Chester hacked Homer's account and steals " << stolen << std::endl;
}

void Chester::PayForProducts()
{
	// AssertIsEnoughMoney(toApu);
	auto& apu = m_contacts.GetAccountPerson(Name::Apu);
	SendMoney(apu.GetAccountId(), toApu);
	std::cout << "Chester buys products from Apu " << toApu << std::endl;
}