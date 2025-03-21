#include "prime.h"
#include <algorithm>
#include <cstdint>
#include <vector>

void CheckArguments(int argumentCount, const std::string& argumentStr)
{
	if (argumentCount != 2)
	{
		throw std::runtime_error("Неверное кол-во аргументов.");
	}

	if (!std::all_of(argumentStr.begin(), argumentStr.end(), isdigit))
	{
		throw std::runtime_error("Аргумент должен быть числом.");
	}
}

SetPrimeNumbers GeneratePrimeNumbersSet(int upperBound)
{
	IsPrimeVectors isPrimes = InitVector(upperBound);
	SieveVector(isPrimes, upperBound);
	return CollectPrimes(isPrimes, upperBound);
}

IsPrimeVectors InitVector(int upperBound)
{
	if (upperBound < 0)
	{
		throw std::runtime_error("Отрицательный предел не может быть.");
	}
	IsPrimeVectors isPrimes(upperBound + 1, true);
	isPrimes[0] = isPrimes[1] = false;
	return isPrimes;
}

SetPrimeNumbers CollectPrimes(const IsPrimeVectors& isPrimes, size_t upperBound)
{
	SetPrimeNumbers primeNumbers;
	if (upperBound >= 2)
	{
		primeNumbers.insert(2);
		for (size_t i = 3; i <= upperBound; i += 2)
		{
			if (isPrimes[i])
			{
				primeNumbers.insert(i);
			}
		}
	}
	return primeNumbers;
}

void SieveVector(IsPrimeVectors& isPrimes, size_t upperBound)
{
	for (size_t i = 3; i * i <= upperBound; i += 2)
	{
		if (!isPrimes[i])
		{
			continue;
		}
		for (size_t j = i * i; j <= upperBound; j += i)
		{
			isPrimes[j] = false;
		}
	}
}

void PrintPrimeNumbers(const SetPrimeNumbers& primeNumbers)
{
	for (const auto& primeNumber : primeNumbers)
	{
		std::cout << primeNumber << '\n';
	}
}