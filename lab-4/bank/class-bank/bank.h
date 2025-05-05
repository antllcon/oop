#ifndef BANK_H
#define BANK_H

#include <iostream>

using AccountId = unsigned long long;
using Money = long long;

class Bank
{
public:
	explicit Bank(Money cash);

	Bank(const Bank&) = delete;
	Bank& operator=(const Bank&) = delete;

	// void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

	// Перевести деньги с исходного счёта (srcAccountId) на целевой (dstAccountId)
	// Нельзя перевести больше, чем есть на исходном счёте
	// Нельзя перевести отрицательное количество денег
	// При нехватке денег на исходном счёте возвращается false
	// Если номера счетов невалидны, выбрасывается BankOperationError
	// При отрицательном количестве денег выбрасывается std::out_of_range
	// [[nodiscard]] bool TrySendMoney(
	// 	AccountId srcAccountId, AccountId dstAccountId, Money amount);

	// Возвращает количество наличных денег в обороте
	// [[nodiscard]] Money GetCash() const;

	// Сообщает о количестве денег на указанном счёте
	// Если указанный счёт отсутствует, выбрасывается исключение BankOperationError
	// Money GetAccountBalance(AccountId accountId) const;

private:
	const Money m_cash;
	Money m_bankCash;
};

#endif // BANK_H