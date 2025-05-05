#include "../class-bank/bank.h"
#include "../class-human/human.h"
#include <memory>
#include <vector>

class Simulation
{
public:
	void Run(int steps);

private:
	Bank bank;
	std::vector<std::unique_ptr<Human>> people;
};