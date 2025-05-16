#include "simulation.h"
#include "../class-apu/apu.h"
#include "../class-bart/bart.h"
#include "../class-berns/berns.h"
#include "../class-chester/chester.h"
#include "../class-homer/homer.h"
#include "../class-lisa/lisa.h"
#include "../class-marge/marge.h"
#include "../class-nelson/nelson.h"
#include "../class-waylon/waylon.h"
#include <iomanip>

Simulation::Simulation(const Money money, const int days)
	: m_simulationMoney(money)
	, m_days(days)
	, m_bank(money)
{
	AssertIsNumberValid(days);
	AssertIsNumberValid(money);
	m_days = days;

	m_actors.personsWithAccount.emplace_back(
		std::make_unique<Homer>(Name::Homer, 0, m_bank, m_contacts));
	m_actors.personsWithAccount.emplace_back(
		std::make_unique<Marge>(Name::Marge, 0, m_bank, m_contacts));
	m_actors.personsWithAccount.emplace_back(
		std::make_unique<Apu>(Name::Apu, 0, m_bank, m_contacts));
	m_actors.personsWithAccount.emplace_back(
		std::make_unique<Berns>(Name::Berns, 0, m_bank, m_contacts));
	m_actors.personsWithAccount.emplace_back(
		std::make_unique<Chester>(Name::Chester, 0, m_bank, m_contacts));
	m_actors.personsWithAccount.emplace_back(
		std::make_unique<Waylon>(Name::Waylon, 0, m_bank, m_contacts));

	m_actors.persons.emplace_back(std::make_unique<Lisa>(Name::Lisa, 0, m_contacts));
	m_actors.persons.emplace_back(std::make_unique<Bart>(Name::Bart, 0, m_contacts));
	m_actors.persons.emplace_back(
		std::make_unique<Nelson>(Name::Nelson, 0, m_contacts));

	DivisionMoney(money);
}

void Simulation::RunSimulation()
{
	for (size_t day = 1; day <= m_days; ++day)
	{
		std::cout << std::endl << "Day #" << day << std::endl;
		std::cout << "=======" << std::endl;

		for (auto& actor : m_actors.personsWithAccount)
		{
			try
			{
				actor->Step();
			}
			catch (const std::exception& error)
			{
				std::cout << "# Actor skip this step: " << error.what() << std::endl;
			}
		}
		for (auto& actor : m_actors.persons)
		{
			try
			{
				actor->Step();
			}
			catch (const std::exception& error)
			{
				std::cout << "# Actor skip this step: " << error.what() << std::endl;
			}
		}

		ShowBalances();
	}
	PrintResults();
}

void Simulation::PrintResults() const
{
	std::cout << "\nResults:" << std::endl;

	Money sum = 0;
	for (auto& actor : m_actors.personsWithAccount)
	{
		sum += actor->GetMoney();
	}
	for (auto& actor : m_actors.persons)
	{
		sum += actor->GetMoney();
	}

	// Сумма наличных денег у персонажей совпадает с суммой наличных денег,
	// зарегистрированных в банке.

	std::cout << "\n== Cash status == " << std::endl;
	std::cout << "Cash form actors: " << sum << std::endl;
	std::cout << "Cash form bank:   " << m_bank.GetCash() << std::endl;

	// Общая сумма всех наличных и безналичных денег на счетах равна сумме, которая
	// изначально была положена в банк в виде наличных.

	std::cout << "The total amount of all cash and deposits in the accounts is "
				 "equal to the amount that was originally deposited in the bank in "
				 "the form of cash.\n"
			  << std::endl;

	std::cout << "Status = ";
	if (sum + m_bank.GetDeposits() == m_simulationMoney)
	{
		std::cout << "[Yes]" << std::endl;
	}
	else
	{
		std::cout << "[False]" << std::endl;
	}
}

const std::string& ToString(Name name);

void Simulation::ShowBalances() const
{
	std::cout << "\nActor balances:\n";
	for (const auto& actor : m_actors.personsWithAccount)
	{
		std::cout << ToString(actor->GetName())
				  << " | Account: " << m_bank.GetAccountBalance(actor->GetAccountId())
				  << " | Cash: " << actor->GetMoney() << "\n";
	}
	for (const auto& actor : m_actors.persons)
	{
		std::cout << ToString(actor->GetName()) << " | Account: -"
				  << " | Cash: " << actor->GetMoney() << "\n";
	}
}

void Simulation::DivisionMoney(Money money)
{
	Money cashForPeople = money
		/ static_cast<Money>(
			m_actors.persons.size() + m_actors.personsWithAccount.size());
	for (const auto& actor : m_actors.personsWithAccount)
	{
		actor->ReceiveCash(cashForPeople);
		actor->Deposit(actor->GetMoney());
	}
	for (const auto& actor : m_actors.persons)
	{
		actor->ReceiveCash(cashForPeople);
	}
}

void Simulation::AssertIsNumberValid(Number number)
{
	if (number < 0)
	{
		throw std::invalid_argument("The number must be a natural number");
	}
}
const std::string& ToString(Name name)
{
	static const std::string homer = "Homer";
	static const std::string marge = "Marge";
	static const std::string lisa = "Lisa";
	static const std::string bart = "Bart";
	static const std::string apu = "Apu";
	static const std::string berns = "Berns";
	static const std::string nelson = "Nelson";
	static const std::string chester = "Chester";
	static const std::string waylon = "Waylon";
	static const std::string unknown = "Unknown";

	switch (name)
	{
	case Name::Homer:
		return homer;
	case Name::Marge:
		return marge;
	case Name::Lisa:
		return lisa;
	case Name::Bart:
		return bart;
	case Name::Apu:
		return apu;
	case Name::Berns:
		return berns;
	case Name::Nelson:
		return nelson;
	case Name::Chester:
		return chester;
	case Name::Waylon:
		return waylon;
	default:
		return unknown;
	}
}