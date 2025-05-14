#include "simulation.h"
#include "../class-apu/apu.h"
#include "../class-bart/bart.h"
#include "../class-berns/berns.h"
#include "../class-homer/homer.h"
#include "../class-lisa/lisa.h"
#include "../class-marge/marge.h"
#include <iomanip>

Simulation::Simulation(const Money money, const int days)
	: m_simulationMoney(money)
	, m_days(days)
	, m_bank(money)
{
	AssertIsNumberValid(days);
	AssertIsNumberValid(money);
	m_days = days;

	m_actors.emplace_back(std::make_unique<Homer>("Homer", 0, m_bank, m_contacts));
	m_actors.emplace_back(std::make_unique<Marge>("Marge", 0, m_bank, m_contacts));
	m_actors.emplace_back(std::make_unique<Lisa>("Lisa ", 0, m_contacts));
	m_actors.emplace_back(std::make_unique<Bart>("Bart ", 0, m_contacts));
	m_actors.emplace_back(std::make_unique<Apu>("Apu", 0, m_bank, m_contacts));
	m_actors.emplace_back(std::make_unique<Berns>("Berns", 0, m_bank, m_contacts));

	DivisionMoney(money);
	OpenAccountsForAll();
}

void Simulation::RunSimulation()
{
	for (size_t day = 1; day <= m_days; ++day)
	{
		std::cout << std::endl << "Day #" << day << std::endl;
		std::cout << "=======" << std::endl;

		for (auto& actor : m_actors)
		{
			try
			{
				actor->Step();
			}
			catch (const std::exception& error)
			{
				// std::cerr << error.what() << std::endl;
				std::cout << actor->GetName() + " skip this step" << std::endl;
			}
		}

		DebugController();
	}
	PrintResults();
}

void Simulation::PrintResults() const
{
	std::cout << "\nResults:\n" << std::endl;

	Money sum = 0;
	for (auto& actor : m_actors)
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

	std::cout << "Status = " << std::endl;
	if (sum + m_bank.GetDeposits() == m_simulationMoney)
	{
		std::cout << "[Yes]";
	}
	else
	{
		std::cout << "[False]";
	}
}

void Simulation::DebugController()
{
	while (true)
	{
		std::cout << "\n[DEBUG MENU]\n";
		std::cout << "1. Skip to the next day\n";
		std::cout << "2. Show balances of all actors\n";
		std::cout << "3. Exit debug mode\n";
		std::cout << "Enter your choice: ";

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "Skipping to the next day...\n";
			return;
		case 2:
			ShowBalances();
			break;
		case 3:
			// StepThroughActors();
			break;
		case 4:
			std::cout << "Exiting debug mode...\n";
			return;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}
}

void Simulation::ShowBalances() const
{
	std::cout << "\n[Actor Balances]\n";
	std::cout << "---------------------------------------\n";
	std::cout << "| Name       | Account Balance | Cash |\n";
	std::cout << "---------------------------------------\n";

	for (const auto& actor : m_actors)
	{
		std::cout << "| " << std::setw(8) << std::left << actor->GetName() << " | ";

		if (const auto* personWithAccount
			= dynamic_cast<const PersonWithAccount*>(actor.get()))
		{
			std::cout << std::setw(15) << std::right
					  << m_bank.GetAccountBalance(personWithAccount->GetAccountId())
					  << " | ";
		}
		else
		{
			std::cout << std::setw(15) << std::right << " - " << " | ";
		}

		std::cout << std::setw(4) << std::right << actor->GetMoney() << " |\n";
	}

	std::cout << "---------------------------------------\n";
}

void Simulation::DivisionMoney(Money money)
{
	Money cashForPeople = money / static_cast<Money>(m_actors.size());
	for (const auto& actor : m_actors)
	{
		actor->ReceiveCash(cashForPeople);
	}
}

void Simulation::OpenAccountsForAll()
{
	for (auto& actor : m_actors)
	{
		if (auto* personWithAccount = dynamic_cast<PersonWithAccount*>(actor.get()))
		{
			personWithAccount->OpenAccount();
			personWithAccount->Deposit(personWithAccount->GetMoney());
		}
	}
}

void Simulation::AssertIsNumberValid(Number number)
{
	if (number < 0)
	{
		throw std::invalid_argument("The number must be a natural number");
	}
}