#include "class-car/car.h"
#include "class-controller/controller.h"
#include <cstdlib>
#include <iostream>

int main()
{
	try
	{
		Car car;
		Controller controller(car, std::cin, std::cout);

		while (true)
		{
			controller.HandleCommand();
		}
	}
	catch (const std::exception& errorMessage)
	{
		std::cerr << errorMessage.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}