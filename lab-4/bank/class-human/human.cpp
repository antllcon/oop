#include "human.h"

Human::Human(const AccountId id, const std::string& name, const Money cash)
	: m_id(id)
	, m_name(name)
	, m_cash(cash)
{
	// Исключения
}