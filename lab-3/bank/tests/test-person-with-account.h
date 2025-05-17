#include "../class-person-with-account/person-with-account.h"

class TestPersonWithAccount : public PersonWithAccount
{
public:
	using PersonWithAccount::PersonWithAccount;
	void Step() override
	{
	}
};
