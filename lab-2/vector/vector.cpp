#include "numbers.h"

int main()
{
	std::vector<double> numbers;

	try
	{
		ReadNumbers(numbers);
		ProcessNumbers(numbers);
		PrintSortedNumbers(numbers);
	}
	catch (const std::exception& errorMessage)
	{
		std::cerr << "Error: " << errorMessage.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}