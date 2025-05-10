#ifndef HOMER_H
#define HOMER_H

#include "../class-bank-user/bank-user.h"
#include "../class-bank/bank.h"
#include "../class-person/person.h"
#include "../types.h"
#include <set>

class Homer : public Person
{
public:
	Homer(Money cash, Person& marge, Person& berns, Person& lisa, Person& bart);

	Homer(const Homer&) = delete;
	Homer& operator=(const Homer&) = delete;

	void Step(Bank& bank);

private:
	void OpenMyAccount(Bank& bank);
	void CloseMyAccount(Bank& bank);

	void GiveMoneyToMarge(Bank& bank);
	void PayElectricity(Bank& bank);
	void GiveMoneyToKids(Bank& bank);

private:
	Person& m_marge;
	Person& m_berns;
	Person& m_lisa;
	Person& m_bart;

	// TODO: сделать как-то лучше?
	static constexpr Money amountToMarge = 100;
	static constexpr Money amountToElectricity = 200;
	static constexpr Money amountToKid = 20;
};

#endif // HOMER_H