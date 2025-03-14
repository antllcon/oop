#include "numbers.h"

// Программа считывает вещественные числа, находит сумму 3 минимальных элементов, прибавляет
// её ко всем числам, сортирует и выводит результат с точностью до 3 знаков. При ошибках ввода
// выводит сообщение и завершается с ошибкой.
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