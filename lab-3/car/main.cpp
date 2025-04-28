#include "class-car/car.h"
#include "class-controller/controller.h"
#include <cstdlib>
#include <iostream>

int main()
{
	Car car;
	Controller controller(car, std::cin, std::cout);
	while (true)
	{
		std::cout << "> ";
		try
		{
			controller.HandleCommand();
		}
		catch (const std::exception& errorMessage)
		{
			std::cerr << errorMessage.what() << std::endl;
		}
	}

	return EXIT_SUCCESS;
}