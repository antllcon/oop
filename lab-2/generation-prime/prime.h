#ifndef PRIME_H
#define PRIME_H

#include <iostream>
#include <set>
#include <vector>

using SetPrimeNumbers = std::set<size_t>;
using IsPrimeVectors = std::vector<bool>;

/// @brief Проверка аргументов входного потока
/// @param argumentCount число переданных параметров
/// @param argumentStr значение переданное вторым аргументом
void CheckArguments(int argumentCount, const std::string& argumentStr);

/// @brief Генерация простых чисел решетом Эратосфена с предварительным просеиванием
/// @param upperBound верхняя граница генерации
/// @return Возвращает множество простых чисел
SetPrimeNumbers GeneratePrimeNumbersSet(int upperBound);

/// @brief Вывод простых чисел
/// @param primeNumbers объект хранящий простые числа
void PrintPrimeNumbers(const SetPrimeNumbers& primeNumbers);

// Инициалзация вектора чисел
IsPrimeVectors InitVector(int upperBound);

// Просеивание вектора с выявлением простых чисел
void SieveVector(IsPrimeVectors& isPrimes, size_t upperBound);

// Сбор простых чисел
SetPrimeNumbers CollectPrimes(const IsPrimeVectors& isPrimes, size_t upperBound);

#endif