#include "nelson.h"
#include <random>

Nelson::Nelson(const std::string& name, Money cash, ContactList& contact)
	: Person(name, cash)
	, m_contacts(contact)
{
	m_contacts.Add(*this);
}

void Nelson::Step()
{
	StealCash();
	PayForCigarettes();
}

void Nelson::StealCash()
{
	auto& bart = m_contacts.GetPerson("Bart");

	Money available = bart.GetMoney();
	if (available <= 0)
	{
		std::cout << GetName() << " tried to steal, but Bart has nothing"
				  << std::endl;
		return;
	}

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<Money> dist(1, available);
	Money stolen = dist(gen);

	bart.SpendCash(stolen);
	ReceiveCash(stolen);

	std::cout << GetName() << " steals " << stolen << " from Bart" << std::endl;
}

void Nelson::PayForCigarettes()
{
	// AssertIsEnoughMoney(toApu);
	auto& apu = m_contacts.GetPerson("Apu");
	TransferTo(apu, toApu);
	std::cout << GetName() << " buys Cigarettes from Apu" << toApu << std::endl;
}