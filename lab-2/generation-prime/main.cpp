#include "lib.h"

// Программа на C++ генерирует множество простых чисел до выбранного верхнего предела (максимум 100
// миллионов) с использованием оптимизированного алгоритма "Решето Эратосфена".  Результат выводится
// в стандартный поток вывода. Проверка: для верхней границы 100 миллионов программа находит 5 761
// 455 простых чисел.
int main(int argc, char* argv[])
{
	try
	{
		CheckArguments(argc, argv[1]);
		const std::string upperBound = argv[1];
		SetPrimeNumbers primeNumbers = GeneratePrimeNumbersSet(stoi(upperBound));
		PrintPrimeNumbers(primeNumbers);
	}
	catch (const std::exception& errorMessage)
	{
		std::cerr << "Error: " << errorMessage.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
