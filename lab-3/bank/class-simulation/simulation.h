#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person/person.h"
#include <memory>
#include <vector>

using Actors = std::vector<std::unique_ptr<Person>>;
using Number = long long;

class Simulation
{
public:
	Simulation(Money money, int days);

	Simulation(const Simulation&) = delete;
	Simulation& operator=(const Simulation&) = delete;

	void RunSimulation();

private:
	void PrintResults() const;
	void DivisionMoney(Money money);
	void DebugController();
	void ShowBalances() const;
	void OpenAccountsForAll();
	static void AssertIsNumberValid(Number number);

private:
	Money m_simulationMoney = 0;
    Number m_days = 0;
	Bank m_bank;
	Actors m_actors;
	ContactList m_contacts;
};