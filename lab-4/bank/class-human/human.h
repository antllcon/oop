#include "../class-bank/bank.h"

class Human
{
public:
	explicit Human(const AccountId id, const std::string& name, const Money cash);

private:
	AccountId m_id;
	std::string m_name;
	Money m_cash;
};