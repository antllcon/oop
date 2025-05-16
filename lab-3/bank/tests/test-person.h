#include "../class-person/person.h"

class TestPerson : public Person
{
public:
	using Person::Person;
	void Step() override
	{
	}
};
