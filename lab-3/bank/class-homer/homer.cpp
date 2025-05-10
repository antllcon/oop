#include "homer.h"

// Что за this?
Homer::Homer(Money cash, BankUser& marge, BankUser& berns, Person& lisa, Person& bart)
	: Person("Homer", cash)
	, m_bankUser(*this)
	, m_marge(marge)
	, m_berns(berns)
	, m_lisa(lisa)
	, m_bart(bart)

{
}

void Homer::OpenMyAccount(Bank& bank)
{
	m_bankUser.OpenAccount(bank);
}

void Homer::CloseMyAccount(Bank& bank)
{
	m_bankUser.CloseAccount(bank);
}

void Homer::GiveMoneyToMarge(Bank& bank)
{
	bank.SendMoney(m_bankUser.GetAccountId(), m_marge.GetAccountId(), amountToMarge);
}

void Homer::PayElectricity(Bank& bank)
{
	bank.SendMoney(
		m_bankUser.GetAccountId(), m_berns.GetAccountId(), amountToElectricity);
}

void Homer::GiveMoneyToKids(Bank& bank)
{
	if (!GetMoney())
	{
		m_bankUser.Withdraw(bank, amountToKid * m_kids.size());
	}

	// Придумать как им переводить денег
	bank.
}
