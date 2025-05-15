#include "chester.h"
#include <random>

Chester::Chester(
	const std::string& name, Money cash, Bank& bank, ContactList& contact)
	: PersonWithAccount(name, cash, bank)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
}

void Chester::Step()
{
	StealDeposit();
	PayForProducts();
}

void Chester::StealDeposit()
{
	auto& homer = m_contacts.GetAccountPerson("Homer");
	Money available = homer.GetDeposit();

	if (available <= 0)
	{
		std::cout << GetName() << " tried to hack Homer, but his account is empty."
				  << std::endl;
		return;
	}

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<Money> dist(1, available);
	Money stolen = dist(gen);

	homer.SendMoney(this->GetAccountId(), stolen);
	std::cout << GetName() << " hacked Homer's account and steals " << stolen
			  << std::endl;
}

void Chester::PayForProducts()
{
	// AssertIsEnoughMoney(toApu);
	auto& apu = m_contacts.GetAccountPerson("Apu");
	SendMoney(apu.GetAccountId(), toApu);
	std::cout << GetName() << " buys products from Apu " << toApu << std::endl;
}