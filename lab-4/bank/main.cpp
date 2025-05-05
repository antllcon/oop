#include <iostream>

int main()
{
	try
	{
	}
	catch (const std::exception& error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
	}

	return EXIT_SUCCESS;
}
