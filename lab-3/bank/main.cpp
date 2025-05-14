#include "class-simulation/simulation.h"
#include <iostream>

struct Arguments
{
	int cash;
	int days;
};

Arguments ParseArgs(int argc, char const* argv[])
{
	Arguments args;
	if (argc != 3)
	{
		throw std::invalid_argument("There should be three arguments: \n\t"
									"1. Program name \n\t"
									"2. The amount of money in cash circulation \n\t"
									"3. The number of simulation days\n");
	}
	args.cash = std::stoi(argv[1]);
	args.days = std::stoi(argv[2]);
	return args;
}

int main(int argc, char const* argv[])
{
	Arguments args;

	try
	{
		auto args = ParseArgs(argc, argv);
		Simulation simulation(args.cash, args.days);
		simulation.RunSimulation();
	}
	catch (const std::exception& error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
	}

	return EXIT_SUCCESS;
}