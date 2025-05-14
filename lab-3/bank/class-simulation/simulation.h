#include "../class-bank/bank.h"
#include "../class-contact/contact-list.h"
#include "../class-person/person.h"
#include <memory>
#include <vector>

using Actors = std::vector<std::unique_ptr<Person>>;

class Simulation
{
public:
	Simulation(const Money money, const int days);

	Simulation(const Simulation&) = delete;
	Simulation& operator=(const Simulation&) = delete;

	void RunSimulation();

private:
	void DivisionMoney(Money money);
	void DebugController();
	void ShowBalances() const;
	void OpenAccountsForAll();
	void AssertIsNumberValid(const int number) const;

private:
	int m_days = 0;
	Bank m_bank;
	Actors m_actors;
	ContactList m_contacts;
};